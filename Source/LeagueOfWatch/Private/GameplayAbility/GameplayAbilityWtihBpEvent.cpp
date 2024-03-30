// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbility/GameplayAbilityWtihBpEvent.h"


void UGameplayAbilityWtihBpEvent::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	K2_OnGiveAbility();

	//TryActivateAbilityOnSpawn(ActorInfo, Spec); <- It is from Lyra. I don't know what the fuck it is
}

void UGameplayAbilityWtihBpEvent::OnRemoveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	K2_OnRemoveAbility();

	Super::OnRemoveAbility(ActorInfo, Spec);
}