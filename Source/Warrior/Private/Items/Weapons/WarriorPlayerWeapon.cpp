// Fill out your copyright notice in the Description page of Project Settings.
#include "Items/Weapons/WarriorPlayerWeapon.h"
#include "GameplayAbilitySpecHandle.h"

void AWarriorPlayerWeapon::SetCachedWeaponAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	CachedWeaponAbilitySpecHandles = InSpecHandles;
}

TArray<FGameplayAbilitySpecHandle> AWarriorPlayerWeapon::GetCachedWeaponAbilitySpecHandles() const
{
	return CachedWeaponAbilitySpecHandles;
}
