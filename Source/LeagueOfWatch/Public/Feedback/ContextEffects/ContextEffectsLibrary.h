// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"
#include "UObject/SoftObjectPath.h"
#include "UObject/WeakObjectPtr.h"

#include "ContextEffectsLibrary.generated.h"

class UNiagaraSystem;
class USoundBase;
struct FFrame;

/**
 *
 */
UENUM()
enum class EContextEffectsLibraryLoadState : uint8
{
	Unloaded = 0,
	Loading = 1,
	Loaded = 2
};

/**
 *
 */
USTRUCT(BlueprintType)
struct LEAGUEOFWATCH_API FContextEffects
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag EffectTag;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer Context;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowedClasses = "/Script/Engine.SoundBase, /Script/Niagara.NiagaraSystem"))
	TArray<FSoftObjectPath> Effects;

};

/**
 *
 */
UCLASS()
class LEAGUEOFWATCH_API UActiveContextEffects : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	FGameplayTag EffectTag;

	UPROPERTY(VisibleAnywhere)
	FGameplayTagContainer Context;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<USoundBase>> Sounds;

	UPROPERTY(VisibleAnywhere)
	TArray<TObjectPtr<UNiagaraSystem>> NiagaraSystems;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FContextEffectLibraryLoadingComplete, TArray<UActiveContextEffects*>, ActiveContextEffects);

/**
 *
 */
UCLASS(BlueprintType)
class LEAGUEOFWATCH_API UContextEffectsLibrary : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FContextEffects> ContextEffects;

	UFUNCTION(BlueprintCallable)
	void GetEffects(const FGameplayTag Effect, const FGameplayTagContainer Context, TArray<USoundBase*>& Sounds, TArray<UNiagaraSystem*>& NiagaraSystems);

	UFUNCTION(BlueprintCallable)
	void LoadEffects();

	EContextEffectsLibraryLoadState GetContextEffectsLibraryLoadState();

private:
	void LoadEffectsInternal();

	void ContextEffectLibraryLoadingComplete(TArray<UActiveContextEffects*> NewActiveContextEffects);

	UPROPERTY(Transient)
	TArray<TObjectPtr<UActiveContextEffects>> ActiveContextEffects;

	UPROPERTY(Transient)
	EContextEffectsLibraryLoadState EffectsLoadState = EContextEffectsLibraryLoadState::Unloaded;
};
