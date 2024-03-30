// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/TagInputConfig.h"

const UInputAction* UTagInputConfig::FindInputAction(const FGameplayTag& InputTag) const
{
	for(const FTagInputAction& Action : InputActions)
	{
		if(Action.InputAction && (Action.InputTag == InputTag))
		{
			return Action.InputAction;
		}
	}

	return nullptr;
}