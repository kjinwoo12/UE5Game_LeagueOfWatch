// Fill out your copyright notice in the Description page of Project Settings.

#pragma warning(disable: 4458)

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

    UWorld* world = GetWorld();

    MultiplayGameMode = Cast<AMultiplayGameMode>(world->GetAuthGameMode());
	MultiplayGameState = world->GetGameState<AMultiplayGameState>();
    MultiplayPlayerState = Cast<AMultiplayPlayerState>(PlayerState);
}
	
void AMultiplayPlayerController::OnGameStateBegin(AMultiplayGameState* MultiplayGameState)
{
    this->MultiplayGameState = MultiplayGameState;

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);

    for(AActor* actor : foundActors)
    {
        IMultiplayEventListener* actorInterface = Cast<IMultiplayEventListener>(actor);
        actorInterface->OnGameStateBegin(MultiplayGameState);
    }

    //If all players are not ready, `ServerRPCReadyForServer()` will be called on `OnPlayerStateBegin`
    if (PlayerStateNum != MultiplayGameState->PlayerArray.Num())
		return;

	ServerRPCReadyForServer();
}

void AMultiplayPlayerController::OnLocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    this->MultiplayPlayerState = MultiplayPlayerState;

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);

    for (AActor* actor : foundActors)
    {
        IMultiplayEventListener* actorInterface = Cast<IMultiplayEventListener>(actor);
        actorInterface->OnLocalPlayerStateBegin(MultiplayPlayerState);
    }

    OnPlayerStateBegin(MultiplayPlayerState);
}

void AMultiplayPlayerController::OnOtherPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    this->MultiplayPlayerState = MultiplayPlayerState;

    TArray<AActor*> foundActors;
    UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);

    for (AActor* actor : foundActors)
    {
        IMultiplayEventListener* actorInterface = Cast<IMultiplayEventListener>(actor);
        actorInterface->OnPlayerStateBegin(MultiplayPlayerState);
    }

    OnPlayerStateBegin(MultiplayPlayerState);
}

void AMultiplayPlayerController::OnPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState)
{
    PlayerStateNum++;

    // If GameState is invalid, `ServerRPCReadyForServer()` will be called on `OnGameStateBegin`
    if (!IsValid(MultiplayGameState))
		return;

    if (PlayerStateNum != MultiplayGameState->PlayerArray.Num())
		return;

    ServerRPCReadyForServer();
}

void AMultiplayPlayerController::ServerRPCReadyForServer_Implementation()
{
	MultiplayGameMode->OnPlayerReady(this);
}

void AMultiplayPlayerController::OnAllPlayersReady()
{
	ClientRPCOnAllPlayersReady();

    TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
		IMultiplayEventListener* actorInterface = Cast<IMultiplayEventListener>(actor);
		actorInterface->OnAllPlayersReady();
	}
}

void AMultiplayPlayerController::ClientRPCOnAllPlayersReady_Implementation()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UMultiplayEventListener::StaticClass(), foundActors);

	for (AActor* actor : foundActors)
	{
		IMultiplayEventListener* actorInterface = Cast<IMultiplayEventListener>(actor);
		actorInterface->OnAllPlayersReady();
	}
}                                        