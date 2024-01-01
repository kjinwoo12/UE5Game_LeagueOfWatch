// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MultiplayGameMode/MultiplayGameMode.h"
#include "GameMode/MultiplayGameMode/MultiplayGameState.h"
#include "GameMode/MultiplayGameMode/MultiplayPlayerController.h"
#include "GameMode/MultiplayGameMode/MultiplayPlayerState.h"


AMultiplayGameMode::AMultiplayGameMode()
{
    GameStateClass = AMultiplayGameState::StaticClass();
    PlayerControllerClass = AMultiplayPlayerController::StaticClass();
    PlayerStateClass = AMultiplayPlayerState::StaticClass();
}

void AMultiplayGameMode::PreLogin(const FString& Options,
                                           const FString& Address,
                                           const FUniqueNetIdRepl& UniqueId,
                                           FString& ErrorMessage)
{
    if (IsGameFullOfPlayers())
    {
        ErrorMessage = "The Game is full of players.";
        return;
    }
}

void AMultiplayGameMode::OnPlayerReady(AMultiplayPlayerController* MultiplayPlayerController)
{
	ReadyPlayers.Add(MultiplayPlayerController);
	PlayerReady(MultiplayPlayerController);

    if (IsAllPlayersReady())
    {
		OnAllPlayersReady();
    }
}

void AMultiplayGameMode::PlayerReady_Implementation(AMultiplayPlayerController* MultiplayPlayerController)
{
}

void AMultiplayGameMode::OnAllPlayersReady()
{
	AllPlayersReady();

    for(AMultiplayPlayerController* ReadyPlayer : ReadyPlayers)
    {
		ReadyPlayer->OnAllPlayersReady();
    }
}

void AMultiplayGameMode::AllPlayersReady_Implementation()
{
}

void AMultiplayGameMode::Logout(AController * Exiting)
{
    AMultiplayPlayerController* multiplayPlayerController = Cast<AMultiplayPlayerController>(Exiting);
    if(IsValid(multiplayPlayerController))
    {
        ReadyPlayers.Remove(multiplayPlayerController);
    }

    Super::Logout(Exiting);
}

bool AMultiplayGameMode::IsGameFullOfPlayers()
{
    AMultiplayGameState* multiplayGameState = GetGameState<AMultiplayGameState>();
    return GetNumPlayers() >= multiplayGameState->PlayerSlotNum;
}

bool AMultiplayGameMode::IsAllPlayersReady()
{
    AMultiplayGameState* multiplayGameState = GetGameState<AMultiplayGameState>();
	return ReadyPlayers.Num() >= multiplayGameState->PlayerSlotNum;
}