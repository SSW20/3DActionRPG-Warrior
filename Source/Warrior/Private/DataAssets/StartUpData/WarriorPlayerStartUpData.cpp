// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/WarriorPlayerStartUpData.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorTypes/WarriorStructType.h"

void UWarriorPlayerStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(InWarriorASC, Level);

	for (const FWarriorWeaponAbility& Ability : PlayerStartUpAbilities)
	{
		if(!Ability.WarriorAbility) continue;

		FGameplayAbilitySpec AbilitySpec(Ability.WarriorAbility);
		AbilitySpec.SourceObject = InWarriorASC->GetAvatarActor();
		AbilitySpec.Level = Level;
		AbilitySpec.DynamicAbilityTags.AddTag(Ability.InputTag);

		InWarriorASC->GiveAbility(AbilitySpec);
	}
}
