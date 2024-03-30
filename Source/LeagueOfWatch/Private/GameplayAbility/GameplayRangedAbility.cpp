// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/GameplayRangedAbility.h"
#include "AbilitySystemComponent.h"
#include "Weapon/WeaponStateComponent.h"
#include "Weapon/RangedWeaponInstance.h"

void UGameplayRangedAbility::StartRangedWeaponTargeting()
{
	check(CurrentActorInfo);

	AActor* AvatarActor = CurrentActorInfo->AvatarActor.Get();
	check(AvatarActor);

	UAbilitySystemComponent* AbilitySystemComponent = CurrentActorInfo->AbilitySystemComponent.Get();
	check(AbilitySystemComponent);

	AController* Controller = GetControllerFromActorInfo();
	check(Controller);
	UWeaponStateComponent* WeaponStateComponent = Controller->FindComponentByClass<UWeaponStateComponent>();

	TArray<FHitResult> FoundHits = PerformLocalTargeting();

	FGameplayAbilityTargetDataHandle TargetDataHandle;
	TargetDataHandle.UniqueId = WeaponStateComponent ? WeaponStateComponent->GetUnconfirmedServerSideHitMarkerCount() : 0;
	
	if(FoundHits.Num() > 0)
	{
		const int32 CartridgeId = FMath::Rand();

		for(const FHitResult& FoundHit : FoundHits)
		{
			FGameplayAbilityTargetData_SingleTargetHit* TargetData = new FGameplayAbilityTargetData_SingleTargetHit();
			TargetData->HitResult = FoundHit;
			TargetDataHandle.Add(TargetData);
		}
	}

	if(WeaponStateComponent)
	{
		WeaponStateComponent->AddUnconfirmedServerSideHitMarkers(TargetDataHandle, FoundHits);
	}

	OnTargetDataReadyCallback(TargetDataHandle, FGameplayTag());
}

AController* UGameplayRangedAbility::GetControllerFromActorInfo() const
{
	if(CurrentActorInfo)
	{
		if(AController* Controller = CurrentActorInfo->PlayerController.Get())
		{
			return Controller;
		}

		AActor* OwnedActor = CurrentActorInfo->OwnerActor.Get();
		while(OwnedActor)
		{
			if(AController* Controller = Cast<AController>(OwnedActor))
			{
				return Controller;
			}

			if(APawn* Pawn = Cast<APawn>(OwnedActor))
			{
				return Pawn->GetController();
			}

			OwnedActor = OwnedActor->GetOwner();
		}
	}
	return nullptr;
}

TArray<FHitResult> UGameplayRangedAbility::PerformLocalTargeting() const
{
	APawn* const AvatarPawn = Cast<APawn>(GetAvatarActorFromActorInfo());

	TArray<FHitResult> HitResults;
	if(AvatarPawn && AvatarPawn->IsLocallyControlled())
	{
		const FTransform TargetTransform = GetCameraTransform(AvatarPawn);
		FVector AimDirection = TargetTransform.GetUnitAxis(EAxis::X) + AbilityParams.AccuracyError;
		FVector StartTrace = TargetTransform.GetTranslation();
		FVector EndTrace = StartTrace + AimDirection * AbilityParams.TraceDistance;

		HitResults = Trace(StartTrace, EndTrace);
		//todo : 총알 여러 개 날아가는 샷건같은 능력에 대응
	}
	return HitResults;
}

TArray<FHitResult> UGameplayRangedAbility::Trace(FVector Start,
												 FVector End) const
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(Trace), true, Avatar);
	TraceParams.bReturnPhysicalMaterial = true;
	if(Avatar)
	{
		TArray<AActor*> AttachedActors;
		Avatar->GetAttachedActors(AttachedActors);
		TraceParams.AddIgnoredActors(AttachedActors);
	}

	TArray<FHitResult> HitResults;
	if(AbilityParams.SweepRadius > 0.0f)
	{
		GetWorld()->SweepMultiByChannel(HitResults,
										Start,
										End,
										FQuat::Identity,
										AbilityParams.TraceChannel,
										FCollisionShape::MakeSphere(AbilityParams.SweepRadius),
										TraceParams);
	}
	else
	{
		GetWorld()->LineTraceMultiByChannel(HitResults,
											Start,
											End,
											AbilityParams.TraceChannel,
											TraceParams);
	}
#if ENABLE_DRAW_DEBUG
	const float LineDebugLifetime = 3.f;
	DrawDebugLine(GetWorld(), Start, End, FColor::Yellow, false, LineDebugLifetime, 0, AbilityParams.SweepRadius * 2);
#endif

	return HitResults;
}

FTransform UGameplayRangedAbility::GetCameraTransform(APawn* SourcePawn) const
{
	check(SourcePawn);

	AController* SourceController = SourcePawn->Controller;
	FVector CameraLocation;
	FRotator CameraRotator;

	if(SourceController)
	{
		APlayerController* PlayerController = Cast<APlayerController>(SourceController);
		if(PlayerController)
		{
			PlayerController->GetPlayerViewPoint(CameraLocation, CameraRotator);
		}
		else
		{
			CameraLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
			CameraRotator = SourceController->GetControlRotation();
		}
		return FTransform(CameraRotator, CameraLocation);
	}
	return FTransform(FRotator(0, 0, 0), FVector(0, 0, 0));
}

void UGameplayRangedAbility::OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
							   FGameplayTag ApplicationTag)
{
	UAbilitySystemComponent* MyAbilityComponent = CurrentActorInfo->AbilitySystemComponent.Get();
	check(MyAbilityComponent);

	if(const FGameplayAbilitySpec *AbilitySpec = MyAbilityComponent->FindAbilitySpecFromHandle(CurrentSpecHandle))
	{
		//FScopedPredictionWindow ScopedPrediction(MyAbilityComponent);

		FGameplayAbilityTargetDataHandle LocalTargetDataHandle(MoveTemp(const_cast<FGameplayAbilityTargetDataHandle&>(TargetDataHandle)));
		const bool bShouldNotifyServer = CurrentActorInfo->IsLocallyControlled() && !CurrentActorInfo->IsNetAuthority();
		if(bShouldNotifyServer)
		{
			MyAbilityComponent->CallServerSetReplicatedTargetData(CurrentSpecHandle, 
																  CurrentActivationInfo.GetActivationPredictionKey(), 
																  LocalTargetDataHandle, 
																  ApplicationTag, 
																  MyAbilityComponent->ScopedPredictionKey);
		}
		
		const bool bIsTargetDataValid = true;
		bool bProjectileWeapon = false;

#if WITH_SERVER_CODE
		if(!bProjectileWeapon)
		{
			if(AController* Controller = GetControllerFromActorInfo())
			{
				if(Controller->GetLocalRole() == ROLE_Authority)
				{
					// Confirm hit markers
					if(UWeaponStateComponent* WeaponStateComponent = Controller->FindComponentByClass<UWeaponStateComponent>())
					{
						TArray<uint8> HitReplaces;
						for(uint8 i = 0; (i < LocalTargetDataHandle.Num()) && (i < 255); ++i)
						{
							if(FGameplayAbilityTargetData_SingleTargetHit* SingleTargetHit = static_cast<FGameplayAbilityTargetData_SingleTargetHit*>(LocalTargetDataHandle.Get(i)))
							{
								if(SingleTargetHit->bHitReplaced)
								{
									HitReplaces.Add(i);
								}
							}
						}

						WeaponStateComponent->ClientConfirmTargetData(LocalTargetDataHandle.UniqueId, bIsTargetDataValid, HitReplaces);
					}

				}
			}
		}
#endif //WITH_SERVER_CODE


		// See if we still have ammo
		if(bIsTargetDataValid && CommitAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo))
		{
			// We fired the weapon, add spread
			URangedWeaponInstance* WeaponData = Cast<URangedWeaponInstance>(AbilitySpec->SourceObject.Get());
			check(WeaponData);
			WeaponData->AddSpread();

			// Let the blueprint do stuff like apply effects to the targets
			OnRangedWeaponTargetDataReady(LocalTargetDataHandle);
		}
		else
		{
			K2_EndAbility();
		}
	}

	// We've processed the data
	MyAbilityComponent->ConsumeClientReplicatedTargetData(CurrentSpecHandle, CurrentActivationInfo.GetActivationPredictionKey());
}