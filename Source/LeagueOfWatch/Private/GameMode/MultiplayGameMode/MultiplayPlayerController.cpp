// Fill out your copyright notice in the Description page of Project Settings.

#include "GameMode/MultiplayGameMode/MultiplayPlayerController.h"
#include "GameMode/MultiplayGameMode/MultiplayGameMode.h"
#include "GameMode/MultiplayGameMode/MultiplayGameState.h"
#include "GameMode/MultiplayGameMode/MultiplayPlayerState.h"
#include "GameMode/MultiplayGameMode/MultiplayEventListener.h"

#include "Kismet/GameplayStatics.h"

void AMultiplayPlayerController::BeginPlay()
{
    if (!HasAuthority())
        return;

	SyncedGameState = GetWorld()->GetGameState<AMultiplayGameState>();
    SyncedPlayerState = Cast<AMultiplayPlayerState>(PlayerState);
}
	
void AMultiplayPlayerController::OnGameStateBegin(AMultiplayGameState* MultiplayGameState)
{
    SyncedGameState = MultiplayGameState;
	GameStateBegin(SyncedGameState);

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);
    for(AActor* actor : foundActors)
    {
        IMultiplayEventListener::Execute_GameStateBegin(actor, MultiplayGameState);
    }

    //If all players are not ready, `ServerRPCPlayerReady()` will be called on `OnPlayerStateBegin`
    if (SyncedGameState->PlayerSlotNum <= PlayerStateNum)
    {
        ServerRPCPlayerReady();
    }
}

void AMultiplayPlayerController::GameStateBegin_Implementation(AMultiplayGameState* MultiplayGameState)
{
}

void AMultiplayPlayerController::OnLocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
	SyncedPlayerState = MultiplayPlayerState;
	LocalPlayerStateBegin(MultiplayPlayerState);

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);
    for (AActor* actor : foundActors)
    {
        IMultiplayEventListener::Execute_LocalPlayerStateBegin(actor, MultiplayPlayerState);
    }

    OnPlayerStateBegin(MultiplayPlayerState);
}

void AMultiplayPlayerController::LocalPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
}

void AMultiplayPlayerController::OnOtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    SyncedPlayerState = MultiplayPlayerState;
	OtherPlayerStateBegin(MultiplayPlayerState);

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);
    for (AActor* actor : foundActors)
    {
        IMultiplayEventListener::Execute_OtherPlayerStateBegin(actor, MultiplayPlayerState);
    }

    OnPlayerStateBegin(MultiplayPlayerState);
}

void AMultiplayPlayerController::OtherPlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
}

void AMultiplayPlayerController::OnPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    PlayerStateNum++;

	PlayerStateBegin(MultiplayPlayerState);

    // If GameState is invalid, `ServerRPCPlayerReady()` will be called on `OnGameStateBegin`
    if (IsValid(SyncedGameState) && SyncedGameState->PlayerSlotNum <= PlayerStateNum)
    {
        ServerRPCPlayerReady();
    }
}

void AMultiplayPlayerController::PlayerStateBegin_Implementation(AMultiplayPlayerState* MultiplayPlayerState)
{
}

void AMultiplayPlayerController::ServerRPCPlayerReady_Implementation()
{
	Cast<AMultiplayGameMode>(GetWorld()->GetAuthGameMode())->OnPlayerReady(this);
}

void AMultiplayPlayerController::OnAllPlayersReady()
{
	ClientRPCOnAllPlayersReady();
}

void AMultiplayPlayerController::ClientRPCOnAllPlayersReady_Implementation()
{
    AllPlayersReady();

    TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
        IMultiplayEventListener::Execute_AllPlayersReady(actor);
	}
}

void AMultiplayPlayerController::AllPlayersReady_Implementation()
{
}