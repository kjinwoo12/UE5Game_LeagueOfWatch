// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentStateComponent.h"
#include "Abilities/GameplayAbility.h"
#include "WeaponStateComponent.generated.h"

struct FScreenSpaceHitLocation
{
	/** Hit location in viewport screenspace */
	FVector2D Location;
	FGameplayTag HitZone;
	bool bShowAsSuccess = false;
};

struct FServerSideHitMarkerBatch
{
	FServerSideHitMarkerBatch() { }

	FServerSideHitMarkerBatch(uint8 InUniqueId) :
		UniqueId(InUniqueId)
	{ }

	TArray<FScreenSpaceHitLocation> Markers;

	uint8 UniqueId = 0;
};

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API UWeaponStateComponent : public UEquipmentStateComponent
{
	GENERATED_BODY()

	TArray<FServerSideHitMarkerBatch> UnconfirmedServerSideHitMarkers;
	
public:

	int GetUnconfirmedServerSideHitMarkerCount() const
	{
		return UnconfirmedServerSideHitMarkers.Num();
	}

	void AddUnconfirmedServerSideHitMarkers(const FGameplayAbilityTargetDataHandle& TargetDataHandle,
											const TArray<FHitResult>& HitResults);

protected:
	bool ShouldShowHitAsSuccess(const FHitResult& Hit) const;
};
