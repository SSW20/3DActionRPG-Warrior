// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/PlayerCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorDebugHelper.h"
#include "WarriorGameplayTags.h"
#include "Items/Weapons/WarriorPlayerWeapon.h"

AWarriorPlayerWeapon* UPlayerCombatComponent::GetPlayerWeaponByTag(FGameplayTag WeaponTag)
{
	return Cast<AWarriorPlayerWeapon>(FindWeaponByTag(WeaponTag));
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
}

void UPlayerCombatComponent::WeaponHitEnd(AActor* TargetActor)
{
	
}
