// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/StartUpData/WarriorStartUpDataBase.h"

#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "UObject/Class.h"
void UWarriorStartUpDataBase::GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASC, int32 Level)
{
	check(InWarriorASC);

	GrantAbilities(OnGivenAbilities, InWarriorASC, Level);
	GrantAbilities(ReactionAbilities, InWarriorASC, Level);

	if (!OnGivenEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& OnGameplayEffectClass : OnGivenEffects)
		{
			UGameplayEffect* Effect = OnGameplayEffectClass->GetDefaultObject<UGameplayEffect>();
			if (Effect)
			{
				InWarriorASC->ApplyGameplayEffectToSelf(Effect, Level, InWarriorASC->MakeEffectContext());
			}

		}
	}
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
