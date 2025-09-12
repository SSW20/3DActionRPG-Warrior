// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorTypes/WarriorStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
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

void UWarriorAbilitySystemComponent::RemovedGrantedPlayerWeaponAbilities(
	TArray<FGameplayAbilitySpecHandle>& InSpecHandles)
{
	if (InSpecHandles.Num() > 0)
	{
		for (const FGameplayAbilitySpecHandle& SpecHandle : InSpecHandles)
		{
			ClearAbility(SpecHandle);
		}
	}
}

void UWarriorAbilitySystemComponent::GrantWeaponAbilities(const TArray<FWarriorWeaponAbility>& Abilities,
	TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles, int32 AbilityLevel)
{
	if (Abilities.Num() > 0)
	{
		for (const FWarriorWeaponAbility& Ability : Abilities)
		{
			FGameplayAbilitySpec AbilitySpec(Ability.WarriorAbility);
			AbilitySpec.SourceObject = GetAvatarActor();
			AbilitySpec.Level = AbilityLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(Ability.InputTag);

			GiveAbility(AbilitySpec);

			OutGrantedAbilitySpecHandles.AddUnique(AbilitySpec.Handle);
		}
		
	}
}

