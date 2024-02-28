// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GameplayTagContainer.h"
#include "AnimLayer.generated.h"


USTRUCT(BlueprintType)
struct FEquipmentAnimLayerSelectionRule
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> Layer;

	UPROPERTY(EditAnywhere, blueprintReadWrite)
	FGameplayTagContainer RequiredTags;
};


USTRUCT(BlueprintType)
struct FAnimLayer
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadwrite)
	TArray<FEquipmentAnimLayerSelectionRule> LayerRules;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UAnimInstance> DefaultLayer;

	TSubclassOf<UAnimInstance> SelectBestLayer(const FGameplayTagContainer& CosmeticTags) const;
};