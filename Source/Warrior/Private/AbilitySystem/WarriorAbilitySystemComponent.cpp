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

bool UWarriorAbilitySystemComponent::TryActivateAbilityByTag(const FGameplayTag Tag)
{
	check(Tag.IsValid())

	TArray<FGameplayAbilitySpec*> MatchesAbilitySpec;
	
	GetActivatableGameplayAbilitySpecsByAllMatchingTags(Tag.GetSingleTagContainer(), MatchesAbilitySpec);

	if (MatchesAbilitySpec.Num() > 0)
	{
		int32 RandIdx = FMath::RandRange(0, MatchesAbilitySpec.Num() - 1);

		FGameplayAbilitySpec* SpecToActive = MatchesAbilitySpec[RandIdx];

		return TryActivateAbility(SpecToActive->Handle);
	}
	return false;
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

