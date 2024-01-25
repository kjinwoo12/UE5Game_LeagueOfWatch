// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdvCharacterMovementComponent.generated.h"

USTRUCT(BlueprintType)
struct FAdvCharacterGroundInfo
{
	GENERATED_BODY()

	FAdvCharacterGroundInfo() :
		LastUpdateFrame(0),
		GroundDistance(0.0f)
	{
	}

	uint64 LastUpdateFrame;

	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API UAdvCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	const FAdvCharacterGroundInfo& GetGroundInfo();

protected:
	FAdvCharacterGroundInfo CachedGroundInfo;
};
