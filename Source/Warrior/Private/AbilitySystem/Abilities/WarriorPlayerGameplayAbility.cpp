// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorPlayerGameplayAbility.h"

#include "Characters/WarriorPlayerCharacter.h"
#include "Controllers/WarriorPlayerController.h"

AWarriorPlayerCharacter* UWarriorPlayerGameplayAbility::GetWarriorPlayerCharacterFromActorInfo() 
{
	if (!CachedWarriorPlayerCharacter.IsValid())
	{
		CachedWarriorPlayerCharacter = Cast<AWarriorPlayerCharacter>(CurrentActorInfo->AvatarActor);
	}
	return CachedWarriorPlayerCharacter.Get();
}

AWarriorPlayerController* UWarriorPlayerGameplayAbility::GetWarriorPlayerControllerFromActorInfo() 
{
	if (!CachedWarriorPlayerController.IsValid())
	{
		CachedWarriorPlayerController = Cast<AWarriorPlayerController>(CurrentActorInfo->PlayerController);
	}
	return CachedWarriorPlayerController.Get();
}

UPlayerCombatComponent* UWarriorPlayerGameplayAbility::GetPlayerCombatComponentFromActorInfo()
{
	return GetWarriorPlayerCharacterFromActorInfo()->GetPlayerCombatComponent();
}

