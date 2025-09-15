// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/Combat/PawnCombatComponent.h"

#include "WarriorDebugHelper.h"
#include "Components/BoxComponent.h"
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

	InWeapon->OnWeaponHitBeginTarget.BindUObject(this, &UPawnCombatComponent::WeaponHitBegin);
	InWeapon->OnWeaponHitEndTarget.BindUObject(this, &UPawnCombatComponent::WeaponHitEnd);

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

void UPawnCombatComponent::ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType Type)
{
	AWarriorWeaponBase* Weapon = GetCurrentEquippedWeapon();
	if (Weapon == nullptr)
	{
		Debug::Print("Weapon is null");
	}
	if (Type == EToggleDamageType::Weapon)
	{
		if (bShouldEnable)
		{
			Weapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}
		else
		{
			Weapon->GetBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
	// TODO : 바디 콜리전 설정도 해야됨
}

void UPawnCombatComponent::WeaponHitBegin(AActor* TargetActor)
{
}

void UPawnCombatComponent::WeaponHitEnd(AActor* TargetActor)
{
}
