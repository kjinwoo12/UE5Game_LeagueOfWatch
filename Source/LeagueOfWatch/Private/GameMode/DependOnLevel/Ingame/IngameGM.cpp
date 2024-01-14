// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DependOnLevel/Ingame/IngameGM.h"
#include "GameMode/DependOnLevel/Ingame/IngameServerEvent.h"
#include "Kismet/GameplayStatics.h"

void AIngameGM::PlayerStateUpdate_Implementation(AMultiplayPlayerController* PlayerController)
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
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), UIngameServerEvent::StaticClass(), foundActors);
	for(AActor* foundActor : foundActors)
	{
		IIngameServerEvent::Execute_AllPlayersReady(foundActor);
	}
}

void AIngameGM::AllPlayersReady_Implementation()
{
}