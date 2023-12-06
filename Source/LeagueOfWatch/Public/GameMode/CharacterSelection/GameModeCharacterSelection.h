// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "GameModeCharacterSelection.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API AGameModeCharacterSelection : public AGameMode
{
	GENERATED_BODY()
	
	/****** Override ******/

	void PreLogin(const FString& Options,
                  const FString& Address,
                  const FUniqueNetIdRepl& UniqueId,
                  FString& ErrorMessage) override;


	/**********************/


public:
    // MaxPlayer Range 0 ~ 255, Default 2.
    UPROPERTY(BlueprintReadWrite)
    int MaxPlayer = 2; 

    // CurrentPlayer Num >= MaxPlayer
    // It follows variable "unit8 MaxPlayer"
	UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsGameFullOfPlayers();
};
