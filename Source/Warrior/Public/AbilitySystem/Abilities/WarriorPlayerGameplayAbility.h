// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorGameplayAbility.h"
#include "WarriorPlayerGameplayAbility.generated.h"

class UPlayerCombatComponent;
class AWarriorPlayerController;
class AWarriorPlayerCharacter;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorPlayerGameplayAbility : public UWarriorGameplayAbility
{
	GENERATED_BODY()
public:

	// 이걸 왜 만들고 저장해놓는지 진짜 모르겠네 ;; << 편하긴 혀
	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorPlayerCharacter* GetWarriorPlayerCharacterFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	AWarriorPlayerController* GetWarriorPlayerControllerFromActorInfo();

	UFUNCTION(BlueprintPure, Category = "Warrior|Ability")
	UPlayerCombatComponent* GetPlayerCombatComponentFromActorInfo();

private:
	TWeakObjectPtr<AWarriorPlayerCharacter> CachedWarriorPlayerCharacter;
	TWeakObjectPtr<AWarriorPlayerController> CachedWarriorPlayerController;
};
