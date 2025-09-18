// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PawnUIComponent.h"
#include "PlayerUIComponent.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponIconChanged, TSoftObjectPtr<UTexture2D>, WeaponIcon);

UCLASS()
class WARRIOR_API UPlayerUIComponent : public UPawnUIComponent
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnPercentChanged OnRageChanged;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnWeaponIconChanged OnWeaponIconChanged;
};
