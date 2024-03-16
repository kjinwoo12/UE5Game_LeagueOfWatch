// Fill out your copyright notice in the Description page of Project Settings.


#include "Teams/TeamSubsystem.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystemGlobals.h"

bool UTeamSubsystem::CanCauseDamage(const UObject* Instigator, const UObject* Target)
{
	ETeamComparison Relationship = CompareTeam(Instigator, Target);
	if(Relationship == ETeamComparison::DifferentTeams)
	{
		return true;
	}
	else if(Relationship == ETeamComparison::InvalidArgument)
	{
		return UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Cast<const AActor>(Target)) != nullptr;
	}
	return false;
}

ETeamComparison UTeamSubsystem::CompareTeam(const UObject* A, const UObject* B)
{
	const IGenericTeamAgentInterface* TeamAInterface = Cast<IGenericTeamAgentInterface>(A);
	if(TeamAInterface)
	{
		return ETeamComparison::InvalidArgument;
	}

	const IGenericTeamAgentInterface* TeamBInterface = Cast<IGenericTeamAgentInterface>(B);
	if(TeamBInterface)
	{
		return ETeamComparison::InvalidArgument;
	}

	FGenericTeamId TeamAId = TeamAInterface->GetGenericTeamId();
	FGenericTeamId TeamBId = TeamBInterface->GetGenericTeamId();
	if(TeamAId == FGenericTeamId::NoTeam || TeamBId == FGenericTeamId::NoTeam)
	{
		return ETeamComparison::InvalidArgument;
	}

	if(TeamAId == TeamBId)
	{
		return ETeamComparison::OnSameTeam;
	}

	return ETeamComparison::DifferentTeams;
}