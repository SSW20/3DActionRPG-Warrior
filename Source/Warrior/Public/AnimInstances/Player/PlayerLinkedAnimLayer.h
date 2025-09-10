// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WarriorPlayerAnimInstance.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "PlayerLinkedAnimLayer.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UPlayerLinkedAnimLayer : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure, meta = (BlueprintThreadSafe))
	UWarriorPlayerAnimInstance* GetPlayerAnimInstance() const;
};
