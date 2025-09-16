// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/Combat/PawnCombatComponent.h"
#include "PlayerCombatComponent.generated.h"

class AWarriorPlayerWeapon;
/**
 * 
 */
UCLASS()
class WARRIOR_API UPlayerCombatComponent : public UPawnCombatComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, Category = "Combat|Weapon")
	AWarriorPlayerWeapon* GetPlayerWeaponByTag(FGameplayTag WeaponTag) const;

	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	AWarriorPlayerWeapon* GetPlayerCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat|Weapon")
	float GetEquippedWeaponBaseDamage(float InLevel) const;
	
	virtual void WeaponHitBegin(AActor* TargetActor) override;
	virtual void WeaponHitEnd(AActor* TargetActor) override;
};
