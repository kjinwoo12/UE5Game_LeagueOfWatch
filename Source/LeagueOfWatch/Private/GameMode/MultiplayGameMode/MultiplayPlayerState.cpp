// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/MultiplayGameMode/MultiplayPlayerState.h"
#include "GameMode/MultiplayGameMode/MultiplayPlayerController.h"

void AMultiplayPlayerState::BeginPlay()
{
    if(HasAuthority())
    {
        //Server
        return;
    }

    AMultiplayPlayerController* localPlayerController = Cast<AMultiplayPlayerController>(GetOwner());
    if (IsValid(localPlayerController))
    { // if the localPlayerController is the owner of this state, 
        localPlayerController->OnLocalPlayerStateBegin(this);
    }
    else
    {
        localPlayerController = GetWorld()->GetFirstPlayerController<AMultiplayPlayerController>();
        if (!IsValid(localPlayerController))
            return;

        localPlayerController->OnOtherPlayerStateBegin(this);
    }
}