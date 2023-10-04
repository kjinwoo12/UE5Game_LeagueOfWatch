// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CombatFormulaFunctionLibrary.h"

float UCombatFormulaFunctionLibrary::ArmoredDamageFormula(float OriginalDamage, float Armor)
{
    float resultDamage = OriginalDamage;

    if (Armor >= 0)
    {
        OriginalDamage /= 1 + Armor * 0.01;
    }
    else
    {
        OriginalDamage /= 2 - 1 / (1 - Armor * 0.01);
    }

    return resultDamage;
}
