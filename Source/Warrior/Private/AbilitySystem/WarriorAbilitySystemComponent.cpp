// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"

void UWarriorAbilitySystemComponent::OnAbilityPressed(FGameplayTag InputTag)
{
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UWarriorAbilitySystemComponent::OnAbilityReleased(FGameplayTag InputTag)
{
}
