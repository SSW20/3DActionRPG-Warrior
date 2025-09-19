// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "WarriorAbilitySystemComponent.generated.h"

struct FWarriorWeaponAbility;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
public:
	void OnAbilityPressed(FGameplayTag InputTag);
	void OnAbilityReleased(FGameplayTag InputTag);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void GrantWeaponAbilities(const TArray<FWarriorWeaponAbility>& Abilities,TArray<FGameplayAbilitySpecHandle>& OutGrantedAbilitySpecHandles, int32 AbilityLevel = 1);

	UFUNCTION(BlueprintCallable, Category = "Warrior|Ability")
	void RemovedGrantedPlayerWeaponAbilities(UPARAM(ref) TArray<FGameplayAbilitySpecHandle>& InSpecHandles);

	UFUNCTION(BlueprintCallable, Category="Warrior|Ability")
	bool TryActivateAbilityByTag(const FGameplayTag Tag);
};
