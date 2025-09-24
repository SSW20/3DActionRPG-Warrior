// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/AbilityTasks/AbilityTask_ExecuteOnTick.h"

UAbilityTask_ExecuteOnTick::UAbilityTask_ExecuteOnTick()
{
	bTickingTask = true;
}

UAbilityTask_ExecuteOnTick* UAbilityTask_ExecuteOnTick::ExecuteTaskOnTick(UGameplayAbility* OwningAbility)
{
	//새로운 어빌리티 태스크 인스턴스를 만들고, 이 태스크를 OwningAbility에 연결하는 함수
	UAbilityTask_ExecuteOnTick* Node = NewAbilityTask<UAbilityTask_ExecuteOnTick>(OwningAbility);
	return Node;
}

void UAbilityTask_ExecuteOnTick::TickTask(float DeltaTime)
{
	Super::TickTask(DeltaTime);

	if (ShouldBroadcastAbilityTaskDelegates())
	{
		OnAbilityTaskTick.Broadcast(DeltaTime);
	}
	else
	{
		EndTask();
	}
}
