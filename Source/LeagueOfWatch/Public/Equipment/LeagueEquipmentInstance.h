// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInstance.h"
#include "Animation/AnimLayer.h"
#include "LeagueEquipmentInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API ULeagueEquipmentInstance : public UEquipmentInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAnimLayer EquippedAnimLayer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FAnimLayer UnequippedAnimLayer;

	UFUNCTION(BlueprintCallable, Category=Animation)
	TSubclassOf<UAnimInstance> GetEquippedAnimInstance(const FGameplayTagContainer& CosmeticTags) const;

	UFUNCTION(BlueprintCallable, Category=Animation)
	TSubclassOf<UAnimInstance> GetUnequippedAnimInstance(const FGameplayTagContainer& CosmeticTags) const;
};
