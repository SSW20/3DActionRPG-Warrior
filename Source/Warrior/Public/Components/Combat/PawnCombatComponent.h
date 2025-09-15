// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/PawnExtensionComponentBase.h"
#include "PawnCombatComponent.generated.h"

class AWarriorWeaponBase;
/**
 * 
 */
UENUM(BlueprintType)
enum class EToggleDamageType : uint8
{
	Weapon,
	LeftHand,
	RightHand
};

UCLASS()
class WARRIOR_API UPawnCombatComponent : public UPawnExtensionComponentBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Combat")
	void RegisterPawnWeapon( FGameplayTag InWeaponTag,  AWarriorWeaponBase* InWeapon, bool bRegisterEquippedWeapon = false);

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AWarriorWeaponBase* FindWeaponByTag(const FGameplayTag InWeaponTag) const;

	UPROPERTY(BlueprintReadWrite, Category = "Combat")
	FGameplayTag CurrentEquippedWeaponTag;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	AWarriorWeaponBase* GetCurrentEquippedWeapon() const;

	UFUNCTION(BlueprintCallable, Category = "Combat")
	void ToggleWeaponCollision(bool bShouldEnable, EToggleDamageType Type = EToggleDamageType::Weapon);

	virtual void WeaponHitBegin(AActor* TargetActor);
	virtual void WeaponHitEnd(AActor* TargetActor);

private:
	TMap<FGameplayTag, AWarriorWeaponBase*> CharacterWeaponsMap;

protected:
	TArray<AActor*> OverlappedActors;
	
};
