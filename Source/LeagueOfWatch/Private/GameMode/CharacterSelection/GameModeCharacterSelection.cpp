// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/CharacterSelection/GameModeCharacterSelection.h"

void AGameModeCharacterSelection::PreLogin(const FString& Options,
                                     const FString& Address,
                                     const FUniqueNetIdRepl& UniqueId,
                                     FString& ErrorMessage) {
    if (IsGameFullOfPlayers())
    {
        ErrorMessage = "The Game is full of players.";
        return;
    }
}

bool AGameModeCharacterSelection::IsGameFullOfPlayers()
{
    int currentPlayerNum = GetNumPlayers();
    if (currentPlayerNum >= MaxPlayer)
    {
        return true;
    }
    return false;
}