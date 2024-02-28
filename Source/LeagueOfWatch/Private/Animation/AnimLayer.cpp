// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/AnimLayer.h"

TSubclassOf<UAnimInstance> FAnimLayer::SelectBestLayer(const FGameplayTagContainer& CosmeticTags) const
{
	for(const FEquipmentAnimLayerSelectionRule& Rule : LayerRules)
	{
		if((Rule.Layer != nullptr) && CosmeticTags.HasAll(Rule.RequiredTags))
		{
			return Rule.Layer;
		}
	}

	return DefaultLayer;
}