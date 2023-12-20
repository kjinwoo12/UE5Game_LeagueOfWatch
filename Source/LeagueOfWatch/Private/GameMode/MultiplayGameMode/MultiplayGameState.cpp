// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MultiplayGameMode/MultiplayGameState.h"
#include "GameMode/MultiplayGameMode/MultiplayPlayerController.h"

void AMultiplayGameState::BeginPlay()
{
    if(HasAuthority())
    {
        //Server
        return;
    }

    AMultiplayPlayerController* localPlayerController = GetWorld()->GetFirstPlayerController<AMultiplayPlayerController>();
    if (!IsValid(localPlayerController))
        return;

    localPlayerController->OnGameStateBegin(this);

}