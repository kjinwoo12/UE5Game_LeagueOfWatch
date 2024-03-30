// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/LeagueInputComponent.h"

template<class UserClass, typename FuncType>
void ULeagueInputComponent::BindAction(const UTagInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent, UserClass* Object, FuncType Func, TArray<uint32>& BindHandles)
{
	check(InputConfig);
	if(const UInputAction* IA = InputConfig->FindInputAction(InputTag))
	{
		BindHandles.Add(BindAction(IA, TriggerEvent, Object, Func));
	}
}

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType>
void ULeagueInputComponent::BindAction(const UTagInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedFunc, TArray<uint32>& BindHandles)
{
	check(InputConfig);

	for(const UInputAction& Action : InputConfig->InputActions)
	{
		if(Action.InputAction && Action.InputTag.IsValid())
		{
			if(PressedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, PressedFunc, Action.InputTag).GetHandle());
			}

			if(ReleasedFunc)
			{
				BindHandles.Add(BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedFunc, Action.InputTag).GetHandle());
			}
		}
	}
}
