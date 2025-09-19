// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorDebugHelper.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/Combat/PawnCombatComponent.h"

void UWarriorGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	if (ActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// 주어진 상태라면 활성화
		ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle);
	}
}

void UWarriorGameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	if (ActivationPolicy == EWarriorAbilityActivationPolicy::OnGiven)
	{
		// 주어진 상태라면 삭제
		ActorInfo->AbilitySystemComponent->ClearAbility(Handle);
	}
}

UPawnCombatComponent* UWarriorGameplayAbility::GetPawnCombatComponent() const
{
	return GetAvatarActorFromActorInfo()->FindComponentByClass<UPawnCombatComponent>();
}

UWarriorAbilitySystemComponent* UWarriorGameplayAbility::GetWarriorAbilitySystemComponent() const
{
	return Cast<UWarriorAbilitySystemComponent>(CurrentActorInfo->AbilitySystemComponent);
}

FActiveGameplayEffectHandle UWarriorGameplayAbility::NativeApplyEffectToTarget(AActor* TargetActor,
	const FGameplayEffectSpecHandle& SpecHandle) const
{
	UWarriorAbilitySystemComponent* TargetASC = Cast<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor));

	check(TargetASC && SpecHandle.IsValid());
	
	return GetWarriorAbilitySystemComponent()->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, TargetASC);

}

FActiveGameplayEffectHandle UWarriorGameplayAbility::BP_ApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle)
{
	return NativeApplyEffectToTarget(TargetActor,SpecHandle);
}


