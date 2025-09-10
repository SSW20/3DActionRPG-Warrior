// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructType.h"
#include "WarriorPlayerWeapon.generated.h"


/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorPlayerWeapon : public AWarriorWeaponBase
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponData")
	FWarriorPlayerWeaponData PlayerWeaponData;
};
