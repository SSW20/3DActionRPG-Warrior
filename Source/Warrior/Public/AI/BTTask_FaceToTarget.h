// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FaceToTarget.generated.h"

/**
 * 
 */

// native , 즉 CPP 에서는 블루프린트처럼 자동적으로 인스턴스화 되지 않아 변수의 값을 재사용할 수 없음
// 하지만 방법이 있다

struct FFaceToTargetTaskMemory
{
	TWeakObjectPtr<AActor> TargetActor;

	TWeakObjectPtr<APawn> OwningPawn;

	bool IsValid() const
	{
		return TargetActor.IsValid() && OwningPawn.IsValid();
	}

	void Reset()
	{
		TargetActor.Reset();
		OwningPawn.Reset();
	}
};


UCLASS()
class WARRIOR_API UBTTask_FaceToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FaceToTarget();

	//~ Begin UBTNode Interface
	virtual void InitializeFromAsset(UBehaviorTree& Asset) override;
	virtual uint16 GetInstanceMemorySize() const override;
	virtual FString GetStaticDescription() const override;
	//~ End UBTNode Interface
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
	bool HasReachedAnglePrecision(const APawn* OwningPawn,const AActor* TargetActor) const;
	
	UPROPERTY(EditAnywhere, Category="Facing Target")
	float AnglePrecision;

	UPROPERTY(EditAnywhere, Category="Facing Target")
	float InterpRotationSpeed;

	UPROPERTY(EditAnywhere, Category="Facing Target")
	FBlackboardKeySelector FacingTargetKey;
};
