// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_PatrolAroundTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BlackboardData.h"
#include "Customizations/MathStructProxyCustomizations.h"
#include "Kismet/KismetMathLibrary.h"

UBTService_PatrolAroundTarget::UBTService_PatrolAroundTarget()
{
	NodeName = TEXT("Native Patrol Around Target");

	INIT_SERVICE_NODE_NOTIFY_FLAGS();

	RotationInterpSpeed = 5.f;
	Interval = 0.f;
	RandomDeviation = 0.f;

	InTargetActorKey.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(ThisClass, InTargetActorKey), AActor::StaticClass());
}

void UBTService_PatrolAroundTarget::InitializeFromAsset(UBehaviorTree& Asset)
{
	Super::InitializeFromAsset(Asset);

	if (UBlackboardData* BBAsset = GetBlackboardAsset())
	{
		InTargetActorKey.ResolveSelectedKey(*BBAsset);
	}
}

FString UBTService_PatrolAroundTarget::GetStaticDescription() const
{
	const FString KeyDescription = InTargetActorKey.SelectedKeyName.ToString();
	
	return FString::Printf(TEXT("Patrol Rotation to %s, Key %s"), *KeyDescription, *GetStaticServiceDescription());
}

void UBTService_PatrolAroundTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

	AActor* TargetActor = Cast<AActor>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(InTargetActorKey.SelectedKeyName));

	if (OwnerPawn && TargetActor)
	{
		FVector OwnerLocation = OwnerPawn->GetActorLocation();
		FVector TargetLocation = TargetActor->GetActorLocation();
		FRotator RotToTarget = UKismetMathLibrary::FindLookAtRotation(OwnerLocation, TargetLocation);
		FRotator DeltaRotToTarget = FMath::RInterpTo(OwnerPawn->GetActorRotation(), RotToTarget, DeltaSeconds, RotationInterpSpeed);
		
		OwnerPawn->SetActorRotation(DeltaRotToTarget);
	}
}


