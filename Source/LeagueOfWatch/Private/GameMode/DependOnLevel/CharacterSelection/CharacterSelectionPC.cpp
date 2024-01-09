// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DependOnLevel/CharacterSelection/CharacterSelectionPC.h"
#include "GameMode/DependOnLevel/CharacterSelection/CharacterSelectionClientEvent.h"
#include "Kismet/GameplayStatics.h"


void ACharacterSelectionPC::AllPlayersReady_Implementation()
{
	ClientRPCBeginCharacterSelection();
}

void ACharacterSelectionPC::ClientRPCBeginCharacterSelection_Implementation()
{
	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UCharacterSelectionClientEvent::StaticClass(), foundActors);
	for(AActor* foundActor : foundActors)
	{
		ICharacterSelectionClientEvent::Execute_BeginCharacterSelectionStage(foundActor);
	}
}