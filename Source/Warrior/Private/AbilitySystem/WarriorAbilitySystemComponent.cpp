// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "WarriorTypes/WarriorStructType.h"
#include "GameplayAbilitySpecHandle.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
void UWarriorAbilitySystemComponent::OnAbilityPressed(FGameplayTag InputTag)
{
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			if (InputTag.MatchesTag(WarriorGameplayTags::InputTag_Toggle) && AbilitySpec.IsActive())
			{
				CancelAbilityHandle(AbilitySpec.Handle);
			}
			else
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}
}

void UWarriorAbilitySystemComponent::OnAbilityReleased(FGameplayTag InputTag)
{
	if (!InputTag.IsValid() || !InputTag.MatchesTag(WarriorGameplayTags::InputTag_Held)) return;

	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
			if (AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
	}
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

void UWarriorAbilitySystemComponent::GrantWeaponAbilities(const TArray<FWarriorWeaponAbility>& Abilities,const TArray<FWarriorHeroSpecialAbilitySet>& SpecialWeaponAbilities,
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
		for (const FWarriorWeaponAbility& SpecialAbility : SpecialWeaponAbilities)
		{
			FGameplayAbilitySpec AbilitySpec(SpecialAbility.WarriorAbility);
			AbilitySpec.SourceObject = GetAvatarActor();
			AbilitySpec.Level = AbilityLevel;
			AbilitySpec.DynamicAbilityTags.AddTag(SpecialAbility.InputTag);

			GiveAbility(AbilitySpec);

			OutGrantedAbilitySpecHandles.AddUnique(AbilitySpec.Handle);
		}
	}
}

