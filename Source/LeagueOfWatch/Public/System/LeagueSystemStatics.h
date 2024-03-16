// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "LeagueSystemStatics.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API ULeagueSystemStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	// Gets all the components that inherit from the given class
	UFUNCTION(BlueprintCallable, Category = "Actor", meta = (DefaultToSelf = "TargetActor", ComponentClass = "/Script/Engine.ActorComponent", DeterminesOutputType = "ComponentClass"))
	static TArray<UActorComponent*> FindComponentsByClass(AActor* TargetActor, TSubclassOf<UActorComponent> ComponentClass, bool bIncludeChildActors = true);
};
