// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_PatrolAroundTarget.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UBTService_PatrolAroundTarget : public UBTService
{
	GENERATED_BODY()

	UBTService_PatrolAroundTarget();

	/* ~Begin UBTNode Interface */
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual FString GetStaticDescription() const override;
	/* ~End UBTNode Interface */

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	UPROPERTY(EditAnywhere, Category="Target")
	FBlackboardKeySelector InTargetActorKey;

	UPROPERTY(EditAnywhere, Category="Target")
	float RotationInterpSpeed;
};
