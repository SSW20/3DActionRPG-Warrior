// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Combat/PawnCombatComponent.h"
#include "Items/Weapons/WarriorWeaponBase.h"


void UPawnCombatComponent::RegisterPawnWeapon(FGameplayTag InWeaponTag, AWarriorWeaponBase* InWeapon,
	bool bRegisterEquippedWeapon)
{
	checkf(!CharacterWeaponsMap.Contains(InWeaponTag), TEXT("Already Has A Weapon"));
	check(InWeapon);

	CharacterWeaponsMap.Emplace(InWeaponTag, InWeapon);

	if (bRegisterEquippedWeapon)
	{
		CurrentEquippedWeaponTag = InWeaponTag;
	}
}

AWarriorWeaponBase* UPawnCombatComponent::FindWeaponByTag(const FGameplayTag InWeaponTag) const
{
	if (CharacterWeaponsMap.Contains(InWeaponTag))
	{
		AWarriorWeaponBase* const* FoundWeapon = CharacterWeaponsMap.Find(InWeaponTag);
		return *FoundWeapon;
	}
	return nullptr;
}

AWarriorWeaponBase* UPawnCombatComponent::GetCurrentEquippedWeapon() const
{
	if (!CurrentEquippedWeaponTag.IsValid()) return nullptr;
	return FindWeaponByTag(CurrentEquippedWeaponTag);
}
