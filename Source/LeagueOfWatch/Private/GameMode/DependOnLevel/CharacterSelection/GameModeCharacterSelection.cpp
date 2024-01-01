// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DependOnLevel/CharacterSelection/GameModeCharacterSelection.h"

void AGameModeCharacterSelection::Shutdown(FString Reason)
{
    RequestEngineExit(TEXT("AGameModeCharacterSelection::Shutdown" + Reason));
}