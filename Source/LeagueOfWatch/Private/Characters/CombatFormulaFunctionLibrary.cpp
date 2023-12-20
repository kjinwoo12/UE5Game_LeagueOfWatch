// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CombatFormulaFunctionLibrary.h"

float UCombatFormulaFunctionLibrary::ArmoredDamageFormula(float originalDamage, float armor)
{
    float resultDamage = originalDamage;

    if (armor >= 0)
    {
        originalDamage /= 1 + armor * 0.01;
    }
    else
    {
        originalDamage /= 2 - 1 / (1 - armor * 0.01);
    }

    return resultDamage;
}
