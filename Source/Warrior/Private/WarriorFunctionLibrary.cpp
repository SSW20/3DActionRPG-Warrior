// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::GetWarriorAbilitySystemComponentFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTag)
{
	UWarriorAbilitySystemComponent* WarriorASC = GetWarriorAbilitySystemComponentFromActor(InActor);
	if (WarriorASC)
	{
		WarriorASC->AddLooseGameplayTag(InTag);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InTag)
{
	UWarriorAbilitySystemComponent* WarriorASC = GetWarriorAbilitySystemComponentFromActor(InActor);
	if (WarriorASC)
	{
		WarriorASC->RemoveLooseGameplayTag(InTag);
	}
}

bool UWarriorFunctionLibrary::NativeDoesActorHasTag(AActor* InActor, FGameplayTag InTag)
{
	UWarriorAbilitySystemComponent* ASC = GetWarriorAbilitySystemComponentFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(InTag))
	{
		return ASC->HasMatchingGameplayTag(InTag);
	}
	return false;
}

bool UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InTag)
{
	return NativeDoesActorHasTag(InActor, InTag);
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (InActor->Implements<UPawnCombatInterface>())
	{
		IPawnCombatInterface* CombatInterface = Cast<IPawnCombatInterface>(InActor);
		return CombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor)
{
	return NativeGetPawnCombatComponentFromActor(InActor);
}
