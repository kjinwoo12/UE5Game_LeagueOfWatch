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

protected:
	UPROPERTY(BlueprintReadOnly)
	TArray<AMultiplayPlayerController*> ReadyPlayers;

public:
	AMultiplayGameMode();

	void PreLogin(const FString& Options,
				  const FString& Address,
				  const FUniqueNetIdRepl& UniqueId,
				  FString& ErrorMessage) override;

	void OnPlayerReady(AMultiplayPlayerController* MultiplayPlayerController);
	UFUNCTION(BlueprintNativeEvent)
	void PlayerReady(AMultiplayPlayerController* MultiplayPlayerController);

	void OnAllPlayersReady();
	UFUNCTION(BlueprintNativeEvent)
	void AllPlayersReady();

	void Logout(AController* Exiting) override;

	// CurrentPlayer Num >= MaxPlayer
	// It follows variable "int MaxPlayer"
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsGameFullOfPlayers();

	UFUNCTION(BlueprintPure)
	bool IsAllPlayersReady();
};
