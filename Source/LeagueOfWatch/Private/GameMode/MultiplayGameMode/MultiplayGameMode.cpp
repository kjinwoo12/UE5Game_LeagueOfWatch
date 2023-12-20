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

void AMultiplayGameMode::BeginPlay()
{

}

void AMultiplayGameMode::OnPlayerReady(AMultiplayPlayerController* MultiplayPlayerController)
{
	ReadyPlayers.Add(MultiplayPlayerController);

    if(ReadyPlayers.Num() == GameState->PlayerArray.Num())
    {
		OnAllPlayerReady();
    }
}

void AMultiplayGameMode::OnAllPlayerReady()
{
    for(AMultiplayPlayerController* ReadyPlayer : ReadyPlayers)
    {
		ReadyPlayer->OnAllPlayersReady();
    }
}