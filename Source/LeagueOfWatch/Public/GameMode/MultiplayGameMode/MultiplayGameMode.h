// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MultiplayGameMode.generated.h"

class AMultiplayPlayerController;

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API AMultiplayGameMode : public AGameModeBase
{
	GENERATED_BODY()

	TArray<AMultiplayPlayerController*> ReadyPlayers;

	AMultiplayGameMode();

	void BeginPlay() override;
	
public:
	virtual void OnPlayerReady(AMultiplayPlayerController* MultiplayPlayerController);

	virtual void OnAllPlayerReady();

};
