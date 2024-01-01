// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MultiplayGameState.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API AMultiplayGameState : public AGameStateBase
{
	GENERATED_BODY()

public:
	// Default 2.
	UPROPERTY(BlueprintReadWrite)
	int PlayerSlotNum=2;

	void BeginPlay() override;
};
