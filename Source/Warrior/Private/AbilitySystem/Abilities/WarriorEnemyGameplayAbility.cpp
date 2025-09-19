// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorEnemyGameplayAbility.h"

#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Characters/WarriorEnemyCharacter.h"

AWarriorEnemyCharacter* UWarriorEnemyGameplayAbility::GetWarriorEnemyCharacterFromActorInfo()
{
	if (!CachedWarriorEnemyCharacter.IsValid())
	{
		CachedWarriorEnemyCharacter = Cast<AWarriorEnemyCharacter>(GetAvatarActorFromActorInfo());
	}
	return CachedWarriorEnemyCharacter.Get();
}

UEnemyCombatComponent* UWarriorEnemyGameplayAbility::GetEnemyCombatComponentFromActorInfo()
{
	return GetWarriorEnemyCharacterFromActorInfo()->GetEnemyCombatComponent();
}

FGameplayEffectSpecHandle UWarriorEnemyGameplayAbility::MakeEnemyEffectSpecHandle(
	TSubclassOf<UGameplayEffect> InEffectClass, FScalableFloat InEnemyDamage)
{
	check(InEffectClass);

	FGameplayEffectContextHandle ContextHandle = GetWarriorAbilitySystemComponent()->MakeEffectContext();
	ContextHandle.SetAbility(this);
	ContextHandle.AddSourceObject(GetAvatarActorFromActorInfo());
	ContextHandle.AddInstigator(GetAvatarActorFromActorInfo(), GetAvatarActorFromActorInfo());

	FGameplayEffectSpecHandle SpecHandle = GetWarriorAbilitySystemComponent()->MakeOutgoingSpec(
		InEffectClass, GetAbilityLevel(), ContextHandle);
	
	SpecHandle.Data.Get()->SetSetByCallerMagnitude(WarriorGameplayTags::Shared_SetByCaller_BaseDamage,
	                                               InEnemyDamage.GetValueAtLevel(GetAbilityLevel()));

	return SpecHandle;
}
