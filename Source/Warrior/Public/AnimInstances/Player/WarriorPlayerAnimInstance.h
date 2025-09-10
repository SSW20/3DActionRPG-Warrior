// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorCharacterAnimInstance.h"
#include "WarriorPlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorPlayerAnimInstance : public UWarriorCharacterAnimInstance
{
	GENERATED_BODY()
public:
	// ABP 에서의 InitializeAnimation과 똑같은 기능
	virtual void NativeInitializeAnimation() override;

	// ABP 에서의 Update + 멀티쓰레드에서 안전함 
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	AWarriorPlayerCharacter* OwningPlayerCharacter;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float RelaxThreshold = 3.f;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bRelaxed = false;

	UPROPERTY()
	float ElapsedTime;
};
