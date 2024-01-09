// Fill out your copyright notice in the Description page of Project Settings.


#include "GameMode/DependOnLevel/CharacterSelection/CharacterSelectionHUD.h"
#include "Blueprint/WidgetBlueprintLibrary.h"

void ACharacterSelectionHUD::BeginCharacterSelectionStage_Implementation()
{
	UE_LOG(LogTemp, Log, TEXT("ACharacterSelectionHUD::BeginCharacterSelectionStage"));
	TArray<UUserWidget*> foundWidgets;
	UWidgetBlueprintLibrary::GetAllWidgetsWithInterface(GetWorld(), foundWidgets, UCharacterSelectionClientEvent::StaticClass(), true);
	for(UUserWidget* widget : foundWidgets)
	{
		ICharacterSelectionClientEvent::Execute_BeginCharacterSelectionStage(widget);
	}
}