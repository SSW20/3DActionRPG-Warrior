// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "WarriorGameplayAbility.generated.h"

class UWarriorAbilitySystemComponent;
class UPawnCombatComponent;

UENUM(BlueprintType)
enum class EWarriorAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

UCLASS()
class WARRIOR_API UWarriorGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	//~ Begin UGameplayAbility Interface.
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;	// Give Ability 이후에 호출
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	//~ End UGameplayAbility Interface
	
	UPROPERTY(EditDefaultsOnly, Category="Warrior|Ability")
	EWarriorAbilityActivationPolicy ActivationPolicy = EWarriorAbilityActivationPolicy::OnTriggered;

	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	UPawnCombatComponent* GetPawnCombatComponent() const;

	UFUNCTION(BlueprintPure, Category="Warrior|Ability")
	UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponent() const;
	
	FActiveGameplayEffectHandle NativeApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle) const;

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Apply Effect To Target"))
	FActiveGameplayEffectHandle BP_ApplyEffectToTarget(AActor* TargetActor, const FGameplayEffectSpecHandle& SpecHandle);

};
