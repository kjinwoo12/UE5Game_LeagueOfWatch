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

public:
	UPROPERTY(BlueprintReadWrite)
	int PlayerStateNum = 0;

public:
	UPROPERTY(BlueprintReadWrite)
	AMultiplayGameState* SyncedGameState;
	UPROPERTY(BlueprintReadWrite)
    AMultiplayPlayerState* SyncedPlayerState;

	void BeginPlay() override;

    void OnGameStateBegin(AMultiplayGameState* MultiplayGameState);
	UFUNCTION(BlueprintNativeEvent)
	void GameStateBegin(AMultiplayGameState* MultiplayGameState);

	void OnLocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);
	UFUNCTION(BlueprintNativeEvent)
	void LocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	void OnOtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);
	UFUNCTION(BlueprintNativeEvent)
	void OtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	void OnPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);
	UFUNCTION(BlueprintNativeEvent)
	void PlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState);

	UFUNCTION(Server, Reliable)
	void ServerRPCPlayerReady();

	void OnAllPlayersReady();

	UFUNCTION(Client, Reliable)
	void ClientRPCOnAllPlayersReady();

	UFUNCTION(BlueprintNativeEvent)
	void AllPlayersReady();
};
