// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerAbility_PickUpStone.h"

#include "Characters/WarriorPlayerCharacter.h"
#include "Items/PickUp/WarriorStoneBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UPlayerAbility_PickUpStone::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                 const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                 const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerAbility_PickUpStone::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerAbility_PickUpStone::SearchStones()
{
	AWarriorPlayerCharacter* Player = GetWarriorPlayerCharacterFromActorInfo();
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		Player,
		Player->GetActorLocation(),
		Player->GetActorLocation() + Player->GetActorUpVector() * SearchDistance,
		BoxSize / 2.f,
		(-Player->GetActorUpVector()).ToOrientationRotator(),
		SearchType,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::None,
		HitResults,
		true
		);

	if (HitResults.IsEmpty())
	{
		CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, false);
	}

	for (FHitResult& HitResult : HitResults)
	{
		if (AWarriorStoneBase* FoundStone = Cast<AWarriorStoneBase>(HitResult.GetActor()))
		{
			CollectedStones.AddUnique(FoundStone);
		}
	}
	
}

void UPlayerAbility_PickUpStone::ConsumeStones()
{
	for (AWarriorStoneBase* Stone : CollectedStones)
	{
		if (Stone)
		{
			Stone->Consumed(GetWarriorAbilitySystemComponent(), GetAbilityLevel());
		}
	}
}
