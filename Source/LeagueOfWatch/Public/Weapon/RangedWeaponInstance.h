// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentInstance.h"
#include "EquipmentTickInterface.h"
#include "RangedWeaponInstance.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API URangedWeaponInstance : public UEquipmentInstance, public IEquipmentTickInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Spread|Fire Params")
	FRuntimeFloatCurve HeatToHeatPerShotCurve;

	UPROPERTY(EditAnywhere, Category = "Spread|Fire Params")
	FRuntimeFloatCurve HeatToCoolDownPerSecondCurve;

	UPROPERTY(EditAnywhere, Category = "Spread|Fire Params")
	FRuntimeFloatCurve HeatToSpreadCurve;

	UPROPERTY(EditAnywhere, Category = "Spread|Fire Params")
	bool bAllowFirstShotAccuracy = false;

	UPROPERTY(EditAnywhere, Category = "Spread|Fire Params", meta = (ForceUnits = s))
	float SpreadRecoveryCooldownDelay = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params", meta = (ForceUnits = "cm/s"))
	float StandingStillSpeedThreshold = 80.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params", meta = (ForceUnits = "cm/s"))
	float StandingStillToMovingSpeedRange = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params", meta = (ForceUnits = x))
	float StandingStillSpreadAngleMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params")
	float StandingStillTransitionRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params", meta = (ForceUnits = x))
	float CrouchingSpreadAngleMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params")
	float CrouchingTransitionRate = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params", meta = (ForceUnits = x))
	float JumpingOrFallingSpreadAngleMultiplier = 1.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Spread|Player Params")
	float JumpingOrFallingTransitionRate = 5.0f;

	UPROPERTY(EditAnywhere, Category = "Spread|Player Params", meta = (ForceUnits = x))
	float AimingSpreadAngleMultiplier = 1.0f;

private:
	float CurrentHeat = 0.0f;

	float CurrentSpreadAngle = 0.0f;

	bool bHasFirstShotAccuracy = false;

	double LastFireTime = 0.0;

	// The current standing still multiplier
	float StandingStillMultiplier = 1.0f;

	// The current crouching multiplier
	float CrouchingMultiplier = 1.0f;

	// The current jumping/falling multiplier
	float JumpFallMultiplier = 1.0f;

	// The current *combined* spread angle multiplier
	float CurrentSpreadAngleMultiplier = 1.0f;
	
public:
	void Tick(float DeltaSeconds) override;

	// Updates the spread and returns true if the spread is at minimum
	bool UpdateSpread(float DeltaSeconds);

	// Updates the multipliers and returns true if they are at minimum
	bool UpdateMultipliers(float DeltaSeconds);

	void AddSpread();

private:
	void ComputeHeatRange(float& MinHeat, float& MaxHeat);

	void ComputeSpreadRange(float& MinSpread, float& MaxSpread);

	inline float ClampHeat(float NewHeat)
	{
		float MinHeat;
		float MaxHeat;
		ComputeHeatRange(MinHeat, MaxHeat);
		return FMath::Clamp(NewHeat, MinHeat, MaxHeat);
	}
};
