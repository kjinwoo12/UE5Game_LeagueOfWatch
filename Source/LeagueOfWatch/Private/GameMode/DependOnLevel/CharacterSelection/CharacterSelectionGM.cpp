// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DependOnLevel/CharacterSelection/CharacterSelectionGM.h"
#include "GameMode/DependOnLevel/CharacterSelection/CharacterSelectionPC.h"
#include "MultiplayPlayerController.h"
#include "Kismet/GameplayStatics.h"

void ACharacterSelectionGM::PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController)
{
	Super::PlayerStateUpdate_Implementation(PlayerController);

	UE_LOG(LogTemp, Log, TEXT("ACharacterSelectionGM::PlayerStateUpdate"));

	if(!IsGameFullOfPlayers())
	{
		UE_LOG(LogTemp, Log, TEXT("ACharacterSelectionGM::PlayerStateUpdate - Players are not full"));
		return;
	}

	if(!IsAllPlayersSynced())
	{
		UE_LOG(LogTemp, Log, TEXT("ACharacterSelectionGM::PlayerStateUpdate - Players are not syncronized"));
		return;
	}

	AllPlayersReady();

	TArray<AActor*> foundActors;
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UCharacterSelectionServerEvent::StaticClass(), foundActors);
	for(AActor* foundActor : foundActors)
	{
		ICharacterSelectionServerEvent::Execute_AllPlayersReady(foundActor);
	}
}

void ACharacterSelectionGM::AllPlayersReady_Implementation()
{
}