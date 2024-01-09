// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MultiplayHUD.h"
#include "CharacterSelectionClientEvent.h"
#include "CharacterSelectionHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API ACharacterSelectionHUD : public AMultiplayHUD, public ICharacterSelectionClientEvent
{
	GENERATED_BODY()

public:
	void BeginCharacterSelectionStage_Implementation();
};
