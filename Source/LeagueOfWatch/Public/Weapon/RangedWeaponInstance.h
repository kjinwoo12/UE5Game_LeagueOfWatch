// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInstance.h"
#include "RangedWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API URangedWeaponInstance : public UEquipmentInstance
{
	GENERATED_BODY()
	
public:
	void Tick(float DeltaSecond);
};
