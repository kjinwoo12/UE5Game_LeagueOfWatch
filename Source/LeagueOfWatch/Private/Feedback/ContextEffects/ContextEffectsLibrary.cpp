// Fill out your copyright notice in the Description page of Project Settings.


#include "Feedback/ContextEffects/ContextEffectsLibrary.h"

#include "NiagaraSystem.h"
#include "Sound/SoundBase.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(ContextEffectsLibrary)


void UContextEffectsLibrary::GetEffects(const FGameplayTag Effect, const FGameplayTagContainer Context,
											TArray<USoundBase*>& Sounds, TArray<UNiagaraSystem*>& NiagaraSystems)
{
	// Make sure Effect is valid and Library is loaded
	if(Effect.IsValid() && Context.IsValid() && EffectsLoadState == EContextEffectsLibraryLoadState::Loaded)
	{
		// Loop through Context Effects
		for(const auto ActiveContextEffect : ActiveContextEffects)
		{
			// Make sure the Effect is an exact Tag Match and ensure the Context has all tags in the Effect (and neither or both are empty)
			if(Effect.MatchesTagExact(ActiveContextEffect->EffectTag)
			   && Context.HasAllExact(ActiveContextEffect->Context)
			   && (ActiveContextEffect->Context.IsEmpty() == Context.IsEmpty()))
			{
				// Get all Matching Sounds and Niagara Systems
				Sounds.Append(ActiveContextEffect->Sounds);
				NiagaraSystems.Append(ActiveContextEffect->NiagaraSystems);
			}
		}
	}
}

void UContextEffectsLibrary::LoadEffects()
{
	// Load Effects into Library if not currently loading
	if(EffectsLoadState != EContextEffectsLibraryLoadState::Loading)
	{
		// Set load state to loading
		EffectsLoadState = EContextEffectsLibraryLoadState::Loading;

		// Clear out any old Active Effects
		ActiveContextEffects.Empty();

		// Call internal loading function
		LoadEffectsInternal();
	}
}

EContextEffectsLibraryLoadState UContextEffectsLibrary::GetContextEffectsLibraryLoadState()
{
	// Return current Load State
	return EffectsLoadState;
}

void UContextEffectsLibrary::LoadEffectsInternal()
{
	// TODO Add Async Loading for Libraries

	// Copy data for async load
	TArray<FContextEffects> LocalContextEffects = ContextEffects;

	// Prepare Active Context Effects Array
	TArray<UActiveContextEffects*> NewActiveContextEffectsArray;

	// Loop through Context Effects
	for(const FContextEffects& ContextEffect : LocalContextEffects)
	{
		// Make sure Tags are Valid
		if(ContextEffect.EffectTag.IsValid() && ContextEffect.Context.IsValid())
		{
			// Create new Active Context Effect
			UActiveContextEffects* NewActiveContextEffects = NewObject<UActiveContextEffects>(this);

			// Pass relevant tag data
			NewActiveContextEffects->EffectTag = ContextEffect.EffectTag;
			NewActiveContextEffects->Context = ContextEffect.Context;

			// Try to load and add Effects to New Active Context Effects
			for(const FSoftObjectPath& Effect : ContextEffect.Effects)
			{
				if(UObject* Object = Effect.TryLoad())
				{
					if(Object->IsA(USoundBase::StaticClass()))
					{
						if(USoundBase* SoundBase = Cast<USoundBase>(Object))
						{
							NewActiveContextEffects->Sounds.Add(SoundBase);
						}
					}
					else if(Object->IsA(UNiagaraSystem::StaticClass()))
					{
						if(UNiagaraSystem* NiagaraSystem = Cast<UNiagaraSystem>(Object))
						{
							NewActiveContextEffects->NiagaraSystems.Add(NiagaraSystem);
						}
					}
				}
			}

			// Add New Active Context to the Active Context Effects Array
			NewActiveContextEffectsArray.Add(NewActiveContextEffects);
		}
	}

	// TODO Call Load Complete after Async Load
	// Mark loading complete
	this->ContextEffectLibraryLoadingComplete(NewActiveContextEffectsArray);
}

void UContextEffectsLibrary::ContextEffectLibraryLoadingComplete(TArray<UActiveContextEffects*> NewActiveContextEffects)
{
	// Flag data as loaded
	EffectsLoadState = EContextEffectsLibraryLoadState::Loaded;

	// Append incoming Context Effects Array to current list of Active Context Effects
	ActiveContextEffects.Append(NewActiveContextEffects);
}