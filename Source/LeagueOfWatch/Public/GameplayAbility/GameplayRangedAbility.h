// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilityWtihBpEvent.h"
#include "GameplayRangedAbility.generated.h"


class UEquipmentInstance;

USTRUCT(BlueprintType)
struct FRangedAbilityParam
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	float TraceDistance = 5000.f;

	UPROPERTY(EditDefaultsOnly)
	float SweepRadius = 0.f;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> TraceChannel;

	UPROPERTY(EditDefaultsOnly)
	FVector AccuracyError;
};

/**
 *
 */
UCLASS()
class LEAGUEOFWATCH_API UGameplayRangedAbility : public UGameplayAbilityWtihBpEvent
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, Category = "Params")
	FRangedAbilityParam AbilityParams;

public:
	UFUNCTION(Blueprintcallable, Category = "Gameplay|Ability")
	void StartRangedWeaponTargeting();

	UFUNCTION(BlueprintCallable, Category = "Gameplay|Ability")
	AController* GetControllerFromActorInfo() const;

protected:
	TArray<FHitResult> PerformLocalTargeting() const;

	UFUNCTION(BlueprintCallable)
	TArray<FHitResult> Trace(FVector Start,
							 FVector End) const;

	FTransform GetCameraTransform(APawn* SourcePawn) const;

	void OnTargetDataReadyCallback(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
								   FGameplayTag ApplicationTag);

	UFUNCTION(BlueprintImplementableEvent)
	void OnRangedWeaponTargetDataReady(const FGameplayAbilityTargetDataHandle& TargetData);
};
