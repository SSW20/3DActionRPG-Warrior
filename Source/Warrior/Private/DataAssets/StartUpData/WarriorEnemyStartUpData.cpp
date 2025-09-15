// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/WarriorEnemyStartUpData.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

void UWarriorEnemyStartUpData::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASC, int32 Level)
{
	Super::GiveToAbilitySystemComponent(InWarriorASC, Level);
	GrantAbilities(EnemyStartUpAbilities,InWarriorASC,Level);
}
