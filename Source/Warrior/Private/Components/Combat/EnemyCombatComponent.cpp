// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Characters/WarriorEnemyCharacter.h"
#include "Components/BoxComponent.h"

void UEnemyCombatComponent::WeaponHitBegin(AActor* TargetActor)
{
	if (OverlappedActors.Contains(TargetActor))
	{
		return;
	}
	
	OverlappedActors.AddUnique(TargetActor);

	//TODO:: Implement block check
	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHasTag(TargetActor, WarriorGameplayTags::Player_Status_Block);
	const bool bIsEnemyAttackUnblockable = UWarriorFunctionLibrary::NativeDoesActorHasTag(GetOwningPawn(), WarriorGameplayTags::Enemy_Status_UnBlockable);

	if (bIsPlayerBlocking && !bIsEnemyAttackUnblockable)
	{
		//TODO::check if the Player block is valid
		if (UWarriorFunctionLibrary::IsBlocked(GetOwningPawn(), TargetActor)) bIsValidBlock = true;
	}
	
	FGameplayEventData Data;
	Data.Instigator = GetOwningPawn();
	Data.Target = TargetActor;
	
	if (bIsValidBlock)
	{
		//TODO::Handle successful Player blocked
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(TargetActor, WarriorGameplayTags::Player_Event_SuccessfulBlock, Data);
	}
	else
	{
		
		Data.EventTag = WarriorGameplayTags::Shared_Event_MeleeHit;
	
		OverlappedActors.AddUnique(TargetActor);
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwningPawn(), WarriorGameplayTags::Shared_Event_MeleeHit, Data);
	}
}

void UEnemyCombatComponent::WeaponHitEnd(AActor* TargetActor)
{
	
}

void UEnemyCombatComponent::ToggleBodyCollision(bool bShouldEnable, EToggleDamageType Type)
{
	AWarriorEnemyCharacter* Owner = Cast<AWarriorEnemyCharacter>(GetOwningPawn());
	check(Owner);
	if (Type == EToggleDamageType::LeftHand)
	{
		if (bShouldEnable)
		{
			Owner->GetLeftHandBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			// 3. Pawn 채널에 대한 응답만 Overlap으로 설정
			Owner->GetLeftHandBoxComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		}
		else
		{
			Owner->GetLeftHandBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
	if (Type == EToggleDamageType::RightHand)
	{
		if (bShouldEnable)
		{
			Owner->GetRightHandBoxComponent()->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
			// 3. Pawn 채널에 대한 응답만 Overlap으로 설정
			Owner->GetRightHandBoxComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
		}
		else
		{
			Owner->GetRightHandBoxComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			OverlappedActors.Empty();
		}
	}
}
