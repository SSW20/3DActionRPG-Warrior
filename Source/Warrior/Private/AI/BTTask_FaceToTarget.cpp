// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FaceToTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_FaceToTarget::UBTTask_FaceToTarget()
{
	NodeName = TEXT("Native Rotate To Facing Target");
	AnglePrecision = 10.f;
	InterpRotationSpeed = 20.f;

	bNotifyTick = true;
	bNotifyTaskFinished = true;
	bCreateNodeInstance = false;

	INIT_TASK_NODE_NOTIFY_FLAGS();

	FacingTargetKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, FacingTargetKey), AActor::StaticClass());
}

void UBTTask_FaceToTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBData = GetBlackboardAsset())
	{
		FacingTargetKey.ResolveSelectedKey(*BBData);
	}
}

uint16 UBTTask_FaceToTarget::GetInstanceMemorySize() const
{
	return sizeof(FFaceToTargetTaskMemory);
}

FString UBTTask_FaceToTarget::GetStaticDescription() const
{
	const FString KeyDescription = FacingTargetKey.SelectedKeyName.ToString();

	return FString::Printf(TEXT("Rotate To Facing Target : %s"), *KeyDescription);
}

EBTNodeResult::Type UBTTask_FaceToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UObject* ActorObject = OwnerComp.GetBlackboardComponent()->GetValueAsObject(FacingTargetKey.SelectedKeyName);
	AActor* TargetActor = Cast<AActor>(ActorObject);
	APawn* OwningPawn = OwnerComp.GetAIOwner()->GetPawn();

	FFaceToTargetTaskMemory* Memory = CastInstanceNodeMemory<FFaceToTargetTaskMemory>(NodeMemory);
	check(Memory);

	Memory->TargetActor = TargetActor;
	Memory->OwningPawn = OwningPawn;

	if (!Memory->IsValid())
	{
		return EBTNodeResult::Failed;
	}
	if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		Memory->Reset();
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::InProgress;
}

void UBTTask_FaceToTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	FFaceToTargetTaskMemory* Memory = CastInstanceNodeMemory<FFaceToTargetTaskMemory>(NodeMemory);
	check(Memory);
	
	if (!Memory->IsValid())
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
	}
	if (HasReachedAnglePrecision(Memory->OwningPawn.Get(), Memory->TargetActor.Get()))
	{
		Memory->Reset();
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
	else
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(Memory->OwningPawn->GetActorLocation(), Memory->TargetActor->GetActorLocation());
		const FRotator DeltaLookAtRot = FMath::RInterpTo(Memory->OwningPawn->GetActorRotation(),
			LookAtRot, DeltaSeconds, InterpRotationSpeed);
		Memory->OwningPawn->SetActorRotation(DeltaLookAtRot);
	}
		
}

bool UBTTask_FaceToTarget::HasReachedAnglePrecision(const APawn* OwningPawn, const AActor* TargetActor) const
{
	const FVector OwnerForward = OwningPawn->GetActorForwardVector();
	const FVector ToTargetNormal = (TargetActor->GetActorLocation()-OwningPawn->GetActorLocation()).GetSafeNormal();
	const float DotValue = FVector::DotProduct(OwnerForward, ToTargetNormal);
	const float ToTargetAngle = UKismetMathLibrary::DegAcos(DotValue);

	return ToTargetAngle <= AnglePrecision;
}

