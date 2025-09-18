// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "WarriorStructType.generated.h"
class UInputMappingContext;
class UWarriorGameplayAbility;
class UPlayerLinkedAnimLayer;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FWarriorWeaponAbility
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UWarriorGameplayAbility> WarriorAbility = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag InputTag;
};

USTRUCT(BlueprintType)
struct FWarriorPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UPlayerLinkedAnimLayer> WeaponAnimLayerToLink;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TArray<FWarriorWeaponAbility> WeaponAbilitySet;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UInputMappingContext* WeaponContextMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FScalableFloat WeaponDamage;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> SoftWeaponIcon;
};
