// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "AbilityTask_WaitEnemySummon.generated.h"

class AWarriorEnemyCharacter;
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitSpawnEnemiesDelegate, const TArray<AWarriorEnemyCharacter*>&, EnemiesToSpawn);

UCLASS()
class WARRIOR_API UAbilityTask_WaitEnemySummon : public UAbilityTask
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, BlueprintInternalUseOnly, meta=(DisplayName = "Wait For Summon Event", HidePin="OwningAbility", DefaultToSelf="OwningAbility", SpawnAmount = "1", RandomSpawnRadius = "200"))
	static UAbilityTask_WaitEnemySummon* WaitEnemySummon(
		UGameplayAbility* OwningAbility,
		TArray<TSoftClassPtr<AWarriorEnemyCharacter>> SoftEnemyClass,
		FGameplayTag EventTag,
		const FVector& SpawnOrigin,
		float SpawnRadius,
		int32 SpawnAmount);


	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate OnSpawnFinished;

	UPROPERTY(BlueprintAssignable)
	FWaitSpawnEnemiesDelegate DidNotSpawn;

	//~ Begin UGameplayTask Interface
	virtual void Activate() override;
	virtual void OnDestroy(bool bInOwnerFinished) override;
	//~ End UGameplayTask Interface

	void OnEventReceived(const FGameplayEventData* EventData);
	void OnEnemyClassesLoaded();
private:
	FGameplayTag CachedEventTag;
	TArray<TSoftClassPtr<AWarriorEnemyCharacter>> CachedSoftEnemyClasses;
	TSoftClassPtr<AWarriorEnemyCharacter> CachedSoftEnemyClass;
	FVector CachedSpawnOrigin;
	float CachedRandomSpawnRadius;
	int32 CachedSpawnAmount;
	FDelegateHandle CachedDelegate;
	
};
