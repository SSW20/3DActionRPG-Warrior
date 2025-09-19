// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "WarriorFunctionLibrary.h"

bool UWarriorBaseAnimInstance::DoesOwnerHaveTag(const FGameplayTag Tag) const
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return UWarriorFunctionLibrary::NativeDoesActorHasTag(OwningPawn, Tag);
	}
	return false;
}
