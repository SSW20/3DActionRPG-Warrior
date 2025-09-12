// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorFunctionLibrary.generated.h"

class UWarriorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable)
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor,FGameplayTag InTag);
	
	static bool NativeDoesActorHasTag(AActor* InActor, FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Does Actor Have Tag"))
	static bool BP_DoesActorHaveTag(AActor* InActor,FGameplayTag InTag);

	
};
