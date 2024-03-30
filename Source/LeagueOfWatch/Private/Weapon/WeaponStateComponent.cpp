// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/WeaponStateComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Physics/PhysicalMaterialWithTags.h"
#include "NativeGameplayTags.h"
#include "Teams/TeamSubsystem.h"
#include "EquipmentComponent.h"
#include "Weapon/RangedWeaponInstance.h"

UE_DEFINE_GAMEPLAY_TAG_STATIC(TAG_Gameplay_Zone, "Gameplay.Zone");

void UWeaponStateComponent::ClientConfirmTargetData_Implementation(uint16 UniqueId, bool bSuccess, const TArray<uint8>& HitReplaces)
{
	for(int i = 0; i < UnconfirmedServerSideHitMarkers.Num(); i++)
	{
		FServerSideHitMarkerBatch& Batch = UnconfirmedServerSideHitMarkers[i];
		if(Batch.UniqueId == UniqueId)
		{
			if(bSuccess && (HitReplaces.Num() != Batch.Markers.Num()))
			{
				UWorld* World = GetWorld();
				bool bFoundShowAsSuccessHit = false;

				int32 HitLocationIndex = 0;
				for(const FScreenSpaceHitLocation& Entry : Batch.Markers)
				{
					if(!HitReplaces.Contains(HitLocationIndex) && Entry.bShowAsSuccess)
					{
						// Only need to do this once
						if(!bFoundShowAsSuccessHit)
						{
							ActuallyUpdateDamageInstigatedTime();
						}

						bFoundShowAsSuccessHit = true;

						LastWeaponDamageScreenLocations.Add(Entry);
					}
					++HitLocationIndex;
				}
			}

			UnconfirmedServerSideHitMarkers.RemoveAt(i);
			break;
		}
	}
}

void UWeaponStateComponent::AddUnconfirmedServerSideHitMarkers(const FGameplayAbilityTargetDataHandle& InTargetData,
															   const TArray<FHitResult>& FoundHits)
{
	FServerSideHitMarkerBatch& NewUnconfirmedHitMarker = UnconfirmedServerSideHitMarkers.Emplace_GetRef(InTargetData.UniqueId);

	if(APlayerController* Owner = GetController<APlayerController>())
	{
		for(const FHitResult& Hit : FoundHits)
		{
			FVector2D HitScreenLocation;
			if(UGameplayStatics::ProjectWorldToScreen(Owner, Hit.Location, /*out*/ HitScreenLocation, /*bPlayerViewportRelative=*/ false))
			{
				FScreenSpaceHitLocation& Entry = NewUnconfirmedHitMarker.Markers.AddDefaulted_GetRef();
				Entry.Location = HitScreenLocation;
				Entry.bShowAsSuccess = ShouldShowHitAsSuccess(Hit);

				// Determine the hit zone
				FGameplayTag HitZone;
				if(const UPhysicalMaterialWithTags* PhysMatWithTags = Cast<const UPhysicalMaterialWithTags>(Hit.PhysMaterial.Get()))
				{
					for(const FGameplayTag MaterialTag : PhysMatWithTags->Tags)
					{
						if(MaterialTag.MatchesTag(TAG_Gameplay_Zone))
						{
							Entry.HitZone = MaterialTag;
							break;
						}
					}
				}
			}
		}
	}
}

bool UWeaponStateComponent::ShouldShowHitAsSuccess(const FHitResult& Hit) const
{
	AActor* HitActor = Hit.GetActor();

	//@TODO: Don't treat a hit that dealt no damage (due to invulnerability or similar) as a success
	UWorld* World = GetWorld();
	if(UTeamSubsystem* TeamSubsystem = UWorld::GetSubsystem<UTeamSubsystem>(GetWorld()))
	{
		return TeamSubsystem->CanCauseDamage(GetController<APlayerController>(), Hit.GetActor());
	}

	return false;
}

void UWeaponStateComponent::ActuallyUpdateDamageInstigatedTime()
{
	UWorld* World = GetWorld();
	if(World->GetTimeSeconds() - LastWeaponDamageInstigatedTime > 0.1)
	{
		LastWeaponDamageScreenLocations.Reset();
	}
	LastWeaponDamageInstigatedTime = World->GetTimeSeconds();
}