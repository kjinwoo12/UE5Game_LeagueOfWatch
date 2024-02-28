// Fill out your copyright notice in the Description page of Project Settings.


#include "Equipment/LeagueEquipmentInstance.h"
#include "EquipmentComponent.h"

TSubclassOf<UAnimInstance> ULeagueEquipmentInstance::GetEquippedAnimInstance(const FGameplayTagContainer& CosmeticTags) const
{
	return EquippedAnimLayer.SelectBestLayer(CosmeticTags);
}

TSubclassOf<UAnimInstance> ULeagueEquipmentInstance::GetUnequippedAnimInstance(const FGameplayTagContainer& CosmeticTags) const
{
	return UnequippedAnimLayer.SelectBestLayer(CosmeticTags);
}