// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "Items/Weapons/WarriorPlayerWeapon.h"

AWarriorPlayerWeapon* UPlayerCombatComponent::GetPlayerWeaponByTag(FGameplayTag WeaponTag) const
{
	return Cast<AWarriorPlayerWeapon>(FindWeaponByTag(WeaponTag));
}

AWarriorPlayerWeapon* UPlayerCombatComponent::GetPlayerCurrentEquippedWeapon() const
{
	return Cast<AWarriorPlayerWeapon>(GetCurrentEquippedWeapon());
}

float UPlayerCombatComponent::GetEquippedWeaponBaseDamage(float InLevel) const
{
	return GetPlayerCurrentEquippedWeapon()->PlayerWeaponData.WeaponDamage.GetValueAtLevel(InLevel);
}

void UPlayerCombatComponent::WeaponHitBegin(AActor* TargetActor)
{
	if (OverlappedActors.Contains(TargetActor))
	{
		return;
	}

	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = TargetActor;
	Data.EventTag = WarriorGameplayTags::Shared_Event_MeleeHit;
	
	OverlappedActors.AddUnique(TargetActor);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Shared_Event_MeleeHit, Data);
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Player_Event_HitPause, FGameplayEventData());
}

void UPlayerCombatComponent::WeaponHitEnd(AActor* TargetActor)
{
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Player_Event_HitPause, FGameplayEventData());
}
