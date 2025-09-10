// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "WarriorStartUpDataBase.generated.h"

class UWarriorAbilitySystemComponent;
class UWarriorGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorStartUpDataBase : public UDataAsset
{
	GENERATED_BODY()
public:
	// ASC에 능력 부여하는 함수
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASC, int32 Level = 1);
protected:
	// 기본 능력들 (무기 생성...)
	UPROPERTY(EditDefaultsOnly, Category = "StartUp")
	TArray<TSubclassOf<UWarriorGameplayAbility>> OnGivenAbilities;

	// 리액션 능력들 (히트 리액션 ...)
	UPROPERTY(EditDefaultsOnly, Category = "StartUp")
	TArray<TSubclassOf<UWarriorGameplayAbility>> ReactionAbilities;

	void GrantAbilities(const TArray<TSubclassOf<UWarriorGameplayAbility>>& AbilitiesToGive, UWarriorAbilitySystemComponent* InWarriorASC, int32 Level = 1);
};
