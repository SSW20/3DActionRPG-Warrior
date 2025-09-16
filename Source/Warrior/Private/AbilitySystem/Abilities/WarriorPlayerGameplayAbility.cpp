// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorPlayerGameplayAbility.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
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

FGameplayEffectSpecHandle UWarriorPlayerGameplayAbility::MakePlayerEffectSpecHandle(TSubclassOf<UGameplayEffect> InEffectClass,
	float InWeaponBaseDamage, FGameplayTag InCurrentAttackTypeTag, int32 InCurrentComboCount)
{
	UWarriorAbilitySystemComponent* WarriorASC = GetWarriorAbilitySystemComponent();
	if (WarriorASC)
	{
		FGameplayEffectContextHandle ContextHandle = WarriorASC->MakeEffectContext();
		ContextHandle.SetAbility(this);
		ContextHandle.AddSourceObject(GetWarriorPlayerCharacterFromActorInfo());
		ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());
		
		FGameplayEffectSpecHandle SpecHandle = WarriorASC->MakeOutgoingSpec(InEffectClass, GetAbilityLevel(), ContextHandle);
		SpecHandle.Data.Get()->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage, InWeaponBaseDamage);

		if (InCurrentAttackTypeTag.IsValid())
		{
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(InCurrentAttackTypeTag, InCurrentComboCount);
		}

		return SpecHandle;
	}
	return nullptr;
}

