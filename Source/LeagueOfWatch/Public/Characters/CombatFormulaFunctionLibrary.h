// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CombatFormulaFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API UCombatFormulaFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	UFUNCTION(BlueprintCallable, Category="CombatFormula")
	static float ArmoredDamageFormula(float OriginalDamage, float Armor);
};
