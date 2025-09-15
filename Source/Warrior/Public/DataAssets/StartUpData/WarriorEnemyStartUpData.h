// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/StartUpData/WarriorStartUpDataBase.h"
#include "WarriorEnemyStartUpData.generated.h"

class UWarriorEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorEnemyStartUpData : public UWarriorStartUpDataBase
{
	GENERATED_BODY()
public:
	virtual void GiveToAbilitySystemComponent(UWarriorAbilitySystemComponent* InWarriorASC, int32 Level = 1) override;
protected:
	// 기본 능력들 (무기 생성...)
	UPROPERTY(EditDefaultsOnly, Category = "StartUp", meta = (TitleProperty="AbilityTag"))
	TArray<TSubclassOf<UWarriorGameplayAbility>> EnemyStartUpAbilities;
};
