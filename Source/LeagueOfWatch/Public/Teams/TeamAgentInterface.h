// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "UObject/Interface.h"
#include "TeamAgentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTeamAgentInterface : public UGenericTeamAgentInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class LEAGUEOFWATCH_API ITeamAgentInterface : public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:

};
