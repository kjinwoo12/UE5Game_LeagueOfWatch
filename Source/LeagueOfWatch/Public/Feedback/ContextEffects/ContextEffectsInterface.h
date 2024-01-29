// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/HitResult.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "ContextEffectsInterface.generated.h"

UENUM()
enum EEffectsContextMatchType : int
{
	ExactMatch,
	BestMatch
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UContextEffectsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEAGUEOFWATCH_API IContextEffectsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AnimMotionEffect(const FName Bone
						  , const FGameplayTag MotionEffect
						  , USceneComponent* StaticMeshComponent
						  , const FVector LocationOffset
						  , const FRotator RotationOffset
						  , const UAnimSequenceBase* AnimationSequence
						  , const bool bHitSuccess
						  , const FHitResult HitResult
						  , FGameplayTagContainer Contexts
						  , FVector VFXScale = FVector(1)
						  , float AudioVolume = 1
						  , float AudioPitch = 1);
};