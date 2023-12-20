// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MultiplayEventListener.generated.h"

class AMultiplayGameState;
class AMultiplayPlayerState;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMultiplayEventListener : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEAGUEOFWATCH_API IMultiplayEventListener
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    virtual void OnGameStateBegin(AMultiplayGameState* MultiplayGameState) = 0;
    virtual void OnLocalPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState) = 0;
    virtual void OnPlayerStateBegin(AMultiplayPlayerState* MultiplayPlayerState) = 0;
	virtual void OnAllPlayersReady() = 0;
};
