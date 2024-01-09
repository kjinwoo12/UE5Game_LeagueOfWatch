// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayPlayerController.h"
#include "CharacterSelectionServerEvent.h"
#include "CharacterSelectionPC.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API ACharacterSelectionPC : 
	public AMultiplayPlayerController,
	public ICharacterSelectionServerEvent
{
	GENERATED_BODY()
public:
	void AllPlayersReady_Implementation() override;

	UFUNCTION(Client, Reliable)
	void ClientRPCBeginCharacterSelection();
};
