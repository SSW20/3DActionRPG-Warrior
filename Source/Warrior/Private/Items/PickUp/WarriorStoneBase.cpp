// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUp/WarriorStoneBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Characters/WarriorPlayerCharacter.h"

void AWarriorStoneBase::Consumed(UWarriorAbilitySystemComponent* WarriorASC, int32 AbilityLevel)
{
	check(EffectClass);
	if (WarriorASC)
	{
		UGameplayEffect* Effect = EffectClass->GetDefaultObject<UGameplayEffect>();
		WarriorASC->ApplyGameplayEffectToSelf(Effect, AbilityLevel, WarriorASC->MakeEffectContext());
	}
	BP_OnConsumed();
}

void AWarriorStoneBase::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AWarriorPlayerCharacter* Player = Cast<AWarriorPlayerCharacter>(OtherActor))
	{
		Player->GetWarriorAbilitySystemComponent()->TryActivateAbilityByTag(WarriorGameplayTags::Player_Ability_PickUp_Stone);
	}
}
