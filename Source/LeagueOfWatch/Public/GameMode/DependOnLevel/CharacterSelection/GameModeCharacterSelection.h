// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameMode/MultiplayGameMode/MultiplayGameMode.h"
#include "GameModeCharacterSelection.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API AGameModeCharacterSelection : public AMultiplayGameMode
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    void Shutdown(FString Reason);
};
