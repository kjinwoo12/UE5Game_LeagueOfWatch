// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeCharacterSelection.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API AGameModeCharacterSelection : public AGameModeBase
{
	GENERATED_BODY()
	
	/****** Override ******/

	void PreLogin(const FString& Options,
                  const FString& Address,
                  const FUniqueNetIdRepl& UniqueId,
                  FString& ErrorMessage) override;


	/**********************/


public:
    // Default 2.
    UPROPERTY(BlueprintReadWrite)
    int MaxPlayer = 2; 

    // CurrentPlayer Num >= MaxPlayer
    // It follows variable "int MaxPlayer"
	UFUNCTION(BlueprintCallable, BlueprintPure)
    bool IsGameFullOfPlayers();

    UFUNCTION(BlueprintCallable)
    void Shutdown(FString Reason);
};
