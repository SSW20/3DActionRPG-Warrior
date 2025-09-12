// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Weapons/WarriorWeaponBase.h"
#include "WarriorTypes/WarriorStructType.h"
#include "WarriorPlayerWeapon.generated.h"


struct FGameplayAbilitySpecHandle;
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

	UFUNCTION(BlueprintCallable)
	void SetCachedWeaponAbilitySpecHandles(const TArray<FGameplayAbilitySpecHandle>& InSpecHandles);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	TArray<FGameplayAbilitySpecHandle> GetCachedWeaponAbilitySpecHandles() const;
private:
	TArray<FGameplayAbilitySpecHandle> CachedWeaponAbilitySpecHandles;
	
	
};
