// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/WarriorStartUpDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UWarriorStartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASC, int32 Level)
{
	check(InWarriorASC);

	GrantAbilities(OnGivenAbilities, InWarriorASC, Level);
	GrantAbilities(ReactionAbilities, InWarriorASC, Level);
}

void UWarriorStartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& AbilitiesToGive,
                                             UWarriorAbilitySystemComponent* InWarriorASC, int32 Level)
{
	if (AbilitiesToGive.Num() == 0) return;

	for (const TSubclassOf<UWarriorGameplayAbility>& Ability : AbilitiesToGive)
	{
		if(!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InWarriorASC->GetAvatarActor();
		AbilitySpec.Level = Level;

		InWarriorASC->GiveAbility(AbilitySpec);
	}
}
