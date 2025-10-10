// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.h"
#include "GameplayTagContainer.h"
#include "PlayerUIComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponIconChanged, TSoftObjectPtr<UTexture2D>, WeaponIcon);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSpecialAbilityChanged, TSoftObjectPtr<UMaterialInterface>, AbilityMaterial, FGameplayTag, InputTag);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAbilityCoolDownChanged, FGameplayTag, InputTag, float, TotalTime, float, RemainTime);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInputAbilityActivated, bool, bActivate);


UCLASS()
class WARRIOR_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChanged OnRageChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeaponIconChanged OnWeaponIconChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSpecialAbilityChanged OnSpecialAbilityChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnAbilityCoolDownChanged OnAbilityCoolDownChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnInputAbilityActivated OnInputAbilityActivated;
};
