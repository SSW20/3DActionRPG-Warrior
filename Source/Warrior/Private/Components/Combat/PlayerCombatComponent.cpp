// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"

#include "Items/Weapons/WarriorPlayerWeapon.h"

AWarriorPlayerWeapon* UPlayerCombatComponent::GetPlayerWeaponByTag(FGameplayTag WeaponTag)
{
	return Cast<AWarriorPlayerWeapon>(FindWeaponByTag(WeaponTag));
}
