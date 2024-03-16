// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "TeamSubsystem.generated.h"

UENUM(BlueprintType)
enum class ETeamComparison
{
	OnSameTeam,
	DifferentTeams,
	InvalidArgument
};

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API UTeamSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	bool CanCauseDamage(const UObject* Instigator, const UObject* Target);

	ETeamComparison CompareTeam(const UObject* A, const UObject* B);
};
