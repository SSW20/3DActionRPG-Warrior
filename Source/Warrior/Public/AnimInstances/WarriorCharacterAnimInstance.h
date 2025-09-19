// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AnimInstances/WarriorBaseAnimInstance.h"
#include "Characters/WarriorCharacterBase.h"
#include "WarriorCharacterAnimInstance.generated.h"

class AWarriorPlayerCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorCharacterAnimInstance : public UWarriorBaseAnimInstance
{
	GENERATED_BODY()
public:
	// ABP 에서의 InitializeAnimation과 똑같은 기능
	virtual void NativeInitializeAnimation() override;

	// ABP 에서의 Update + 멀티쓰레드에서 안전함 
	virtual void NativeThreadSafeUpdateAnimation(float DeltaSeconds) override;


// protected:
	// ABP 이벤트그래프에서 쓰는 내용들을 CPP 에서 쓰는 법
	UPROPERTY()
	AWarriorCharacterBase* OwningCharacter;

	UPROPERTY()
	UCharacterMovementComponent* OwningMovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	bool bHasAcceleration;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AnimData|LocomotionData")
	float LocomotionDirection;
};
