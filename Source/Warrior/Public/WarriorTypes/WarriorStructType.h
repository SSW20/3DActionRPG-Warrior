// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarriorStructType.generated.h"
class UPlayerLinkedAnimLayer;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FWarriorPlayerWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	TSubclassOf<UPlayerLinkedAnimLayer> WeaponAnimLayerToLink;
};
