// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IngameServerEvent.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIngameServerEvent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEAGUEOFWATCH_API IIngameServerEvent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent)
	void AllPlayersReady();
};
