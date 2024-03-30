// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "TagInputConfig.h"
#include "LeagueInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class LEAGUEOFWATCH_API ULeagueInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template<class UserClass, typename FuncType>
	void BindAction(const UTagInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, TArray<uint32>& BindHandles);

	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
	void BindAction(const UTagInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles);
};
