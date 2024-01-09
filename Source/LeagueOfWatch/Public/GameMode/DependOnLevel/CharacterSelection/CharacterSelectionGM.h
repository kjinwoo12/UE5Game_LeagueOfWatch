// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayGameMode.h"
#include "CharacterSelectionGM.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API ACharacterSelectionGM : public AMultiplayGameMode
{
	GENERATED_BODY()
	
public:
	void PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController) override;

	UFUNCTION(BlueprintNativeEvent)
	void AllPlayersReady();
};
