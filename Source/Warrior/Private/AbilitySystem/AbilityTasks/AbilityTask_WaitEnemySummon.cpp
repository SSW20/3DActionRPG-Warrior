// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AbilityTask_WaitEnemySummon.h"

#include "AbilitySystemComponent.h"
#include "NavigationSystem.h"
#include "Characters/WarriorEnemyCharacter.h"
#include "Engine/AssetManager.h"

UAbilityTask_WaitEnemySummon* UAbilityTask_WaitEnemySummon::WaitEnemySummon(UGameplayAbility* OwningAbility,
                                                                            TArray<TSoftClassPtr<AWarriorEnemyCharacter>> SoftEnemyClass, FGameplayTag EventTag, const FVector& SpawnOrigin,
                                                                            float SpawnRadius, int32 SpawnAmount)
{
	UAbilityTask_WaitEnemySummon* Task = NewAbilityTask<UAbilityTask_WaitEnemySummon>(OwningAbility);
	Task->CachedEventTag = EventTag;
	Task->CachedSpawnOrigin = SpawnOrigin;
	Task->CachedRandomSpawnRadius = SpawnRadius;
	Task->CachedSpawnAmount = SpawnAmount;
	Task->CachedSoftEnemyClasses = SoftEnemyClass;

	return Task;
}

void UAbilityTask_WaitEnemySummon::Activate()
{
	// Cached Event Tag에 해당하는 델레게이트를 생성 or 찾은 뒤 반환
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);

	// 2. 함수 연결 및 핸들 저장
	CachedDelegate = Delegate.AddUObject(this, &UAbilityTask_WaitEnemySummon::OnEventReceived);
}

void UAbilityTask_WaitEnemySummon::OnDestroy(bool bInOwnerFinished)
{
	FGameplayEventMulticastDelegate& Delegate = AbilitySystemComponent->GenericGameplayEventCallbacks.FindOrAdd(CachedEventTag);
	Delegate.Remove(CachedDelegate);
	
	Super::OnDestroy(bInOwnerFinished);
}

void UAbilityTask_WaitEnemySummon::OnEventReceived(const FGameplayEventData* EventData)
{
	if (!CachedSoftEnemyClasses.IsEmpty())
	{
		TArray<FSoftObjectPath> SoftPathsToLoad;
		for (const TSoftClassPtr<AWarriorEnemyCharacter>& SoftClassPtr : CachedSoftEnemyClasses)
		{
			if (!SoftClassPtr.IsNull())
			{
				SoftPathsToLoad.Add(SoftClassPtr.ToSoftObjectPath());
			}
		}
        
		// 유효한 로드 경로가 없으면 실패 처리 후 종료
		if (SoftPathsToLoad.IsEmpty())
		{
			if (ShouldBroadcastAbilityTaskDelegates())
			{
				DidNotSpawn.Broadcast(TArray<AWarriorEnemyCharacter*>());
			}
			EndTask();
			return;
		}
		UAssetManager::Get().GetStreamableManager().RequestAsyncLoad(SoftPathsToLoad,FStreamableDelegate::CreateUObject(this,
				                                                       &UAbilityTask_WaitEnemySummon::OnEnemyClassesLoaded));
	}
}


void UAbilityTask_WaitEnemySummon::OnEnemyClassesLoaded()
{
	UWorld* World = GetWorld();

	if (!World)
	{
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			DidNotSpawn.Broadcast(TArray<AWarriorEnemyCharacter*>());
		}
		EndTask();
		return;
	}

	TArray<AWarriorEnemyCharacter*> SpawnedEnemies;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	FVector SpawnLocation = FVector(0,0,300.f);
	FRotator SpawnRotation = AbilitySystemComponent->GetAvatarActor()->GetActorForwardVector().ToOrientationRotator();

	for (int32 i = 0; i < CachedSpawnAmount; ++i)
	{
		UClass* EnemyClass = CachedSoftEnemyClasses[FMath::RandRange(0, CachedSoftEnemyClasses.Num() - 1)].Get();
		UNavigationSystemV1::K2_GetRandomReachablePointInRadius(this, CachedSpawnOrigin, SpawnLocation, CachedRandomSpawnRadius);

		AWarriorEnemyCharacter* SpawnedEnemy = World->SpawnActor<AWarriorEnemyCharacter>(EnemyClass,SpawnLocation, SpawnRotation, SpawnParams);
		if (SpawnedEnemy)
		{
			SpawnedEnemies.Add(SpawnedEnemy);
		}
		
		if (ShouldBroadcastAbilityTaskDelegates())
		{
			if (!SpawnedEnemies.IsEmpty())
			{
				OnSpawnFinished.Broadcast(SpawnedEnemies);
			}
			else
			{
				DidNotSpawn.Broadcast(TArray<AWarriorEnemyCharacter*>());
			}
		}
	}
	EndTask();
}
