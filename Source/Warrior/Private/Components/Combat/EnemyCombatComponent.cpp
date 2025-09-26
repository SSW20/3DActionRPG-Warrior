// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
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

	const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHasTag(TargetActor, WarriorGameplayTags::Player_Status_Block);
	const bool bIsEnemyAttackUnblockable = UWarriorFunctionLibrary::NativeDoesActorHasTag(GetOwningPawn(), WarriorGameplayTags::Enemy_Status_UnBlockable);

	if (bIsPlayerBlocking && !bIsEnemyAttackUnblockable)
	{
		//TODO::check if the Player block is valid
		if (UWarriorFunctionLibrary::IsBlocked(GetOwningPawn(), TargetActor)) bIsValidBlock = true;
	}
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = TargetActor;
	
	if (bIsValidBlock)
	{
		//TODO::Handle successful Player blocked
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, WarriorGameplayTags::Player_Event_SuccessfulBlock, Data);
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
