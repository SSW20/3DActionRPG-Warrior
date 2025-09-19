// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"

void UEnemyCombatComponent::WeaponHitBegin(AActor* TargetActor)
{
	if (OverlappedActors.Contains(TargetActor))
	{
		return;
	}
	
	OverlappedActors.AddUnique(TargetActor);

	//TODO:: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = false;
	const bool bIsEnemyAttackUnblockable = false;

	if (bIsPlayerBlocking && !bIsEnemyAttackUnblockable)
	{
		//TODO::check if the Player block is valid
	}
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = TargetActor;
	
	if (bIsValidBlock)
	{
		//TODO::Handle successful Player blocked
	}
	else
	{
		
		Data.EventTag = WarriorGameplayTags::Shared_Event_MeleeHit;
	
		OverlappedActors.AddUnique(TargetActor);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Shared_Event_MeleeHit, Data);
	}
}

void UEnemyCombatComponent::WeaponHitEnd(AActor* TargetActor)
{
	
}
