// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MultiplayPlayerController.generated.h"

/**
 * 
 */
class AMultiplayGameState;
class AMultiplayPlayerState;
class AMultiplayGameMode;

UCLASS()
class LEAGUEOFWATCH_API AMultiplayPlayerController : public APlayerController
{
	GENERATED_BODY()

	AMultiplayGameMode* MultiplayGameMode;
	AMultiplayGameState* MultiplayGameState;
    AMultiplayPlayerState* MultiplayPlayerState;
    int PlayerStateNum = 0;

	void BeginPlay() override;

public:
    virtual void OnGameStateBegin(AMultiplayGameState* MultiplayGameState);

	virtual void OnLocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	virtual void OnOtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	virtual void OnPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	UFUNCTION(Server, Reliable)
	void ServerRPCReadyForServer();

	void OnAllPlayersReady();

	UFUNCTION(Client, Reliable)
	void ClientRPCOnAllPlayersReady();
};
