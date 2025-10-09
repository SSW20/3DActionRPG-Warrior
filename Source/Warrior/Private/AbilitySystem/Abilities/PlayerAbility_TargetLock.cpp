// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/PlayerAbility_TargetLock.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/WarriorPlayerCharacter.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"
#include "Controllers/WarriorPlayerController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Widgets/WarriorWidgetBase.h"
#include "Kismet/KismetSystemLibrary.h"

void UPlayerAbility_TargetLock::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                        const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                        const FGameplayEventData* TriggerEventData)
{
	
	TryLockOnTarget();
	InitCharacterWalkSpeed();
	InitMappingContext();
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UPlayerAbility_TargetLock::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{	
	CleanUp();
	ResetCharacterWalkSpeed();
	ResetMappingContext();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UPlayerAbility_TargetLock::TryLockOnTarget()
{
	FindOtherTarget();
	if (CurrentNearestTarget == nullptr)
	{
		CancelTargetLockAbility();
	}
	else
	{
		DrawLockWidget();
		SetTargetLockWidgetPosition();
	}
	
}

void UPlayerAbility_TargetLock::GetAvailableTargetsToLock()
{
	TArray<FHitResult> HitResults;
	UKismetSystemLibrary::BoxTraceMultiForObjects(
		GetAvatarActorFromActorInfo(),
		GetWarriorPlayerCharacterFromActorInfo()->GetActorLocation(),
		GetWarriorPlayerCharacterFromActorInfo()->GetActorForwardVector() * DetectionRange,
		BoxSize / 2.f,
		GetWarriorPlayerCharacterFromActorInfo()->GetActorForwardVector().ToOrientationRotator(),
		ObjectTypesToSearch,
		false,
		TArray<AActor*>(),
		bDrawDebugType ? EDrawDebugTrace::None : EDrawDebugTrace::Persistent,
		HitResults,
		true);

	if (HitResults.Num() > 0)
	{
		for (FHitResult& HitResult : HitResults)
		{
			if (AActor* Actor = HitResult.GetActor())
			{
				if (Actor != GetWarriorPlayerCharacterFromActorInfo() && !UWarriorFunctionLibrary::NativeDoesActorHasTag(Actor, WarriorGameplayTags::Shared_Status_Death))
				{
					FoundTargets.AddUnique(Actor);
				}
			}
		}
	}
}

void UPlayerAbility_TargetLock::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UPlayerAbility_TargetLock::CleanUp()
{
	FoundTargets.Empty();
	CurrentNearestTarget = nullptr;
	if (TargetLockWidget) TargetLockWidget->RemoveFromParent();
	TargetLockWidget	= nullptr;
	WidgetSize = FVector2D::ZeroVector;
}

void UPlayerAbility_TargetLock::ResetCharacterWalkSpeed()
{
	if (CachedMaxWalkSpeed > 0.f)
	{
		GetWarriorPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = CachedMaxWalkSpeed;
	}
	CachedMaxWalkSpeed = 0;
}

void UPlayerAbility_TargetLock::ResetMappingContext()
{
	if (!GetWarriorPlayerControllerFromActorInfo()) return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetWarriorPlayerControllerFromActorInfo()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->RemoveMappingContext(TargetLockMappingContext);
}

AActor* UPlayerAbility_TargetLock::FindNearestTarget(const TArray<AActor*>& FoundActors)
{
	AActor* NearestTarget = UGameplayStatics::FindNearestActor(GetWarriorPlayerCharacterFromActorInfo()->GetActorLocation(),FoundActors, DetectionRange);
	if (NearestTarget)
	{
		return NearestTarget;
	}
	return nullptr;
}

void UPlayerAbility_TargetLock::DrawLockWidget()
{
	if (TargetLockWidget == nullptr)
	{
		check(TargetLockWidgetClass);
		TargetLockWidget = CreateWidget<UWarriorWidgetBase>(GetWarriorPlayerControllerFromActorInfo(),TargetLockWidgetClass);
		check(TargetLockWidget);
		TargetLockWidget->AddToViewport();
	}
}

void UPlayerAbility_TargetLock::SetTargetLockWidgetPosition()
{
	if (!TargetLockWidget || !CurrentNearestTarget)
	{
		CancelTargetLockAbility();
		return;
	}
	FVector2D ScreenLocation;
	//3D 월드 공간에 있는 위치를 2D 위젯(UI) 공간의 스크린 좌표로 변환하는 함수
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		GetWarriorPlayerControllerFromActorInfo(),	//어느 플레이어의 화면에 위치를 투영할지 결정
		CurrentNearestTarget->GetActorLocation(),	//변환하려는 월드 공간의 3D 위치, 스크린 좌표로 변환될 대상
		ScreenLocation,							// 변환된 2D 스크린 좌표를 저장할 변수
		true);

	// WidgetTree에는 TargetLockWidget의 모든 위젯이 포함되어있음
	if (WidgetSize == FVector2D::ZeroVector)
	{
		TargetLockWidget->WidgetTree->ForEachWidget([this](UWidget* WidgetFound)
	   {
		   if (USizeBox* SizeBox = Cast<USizeBox>(WidgetFound))
		   {
				WidgetSize.X = SizeBox->GetWidthOverride();
		   		WidgetSize.Y = SizeBox->GetHeightOverride();
		   }
	   });
	}

	// 위젯의 사이즈도 고려
	ScreenLocation -= WidgetSize / 2.f; 

	TargetLockWidget->SetPositionInViewport(ScreenLocation, false);
}

void UPlayerAbility_TargetLock::InitCharacterWalkSpeed()
{
	if (CurrentNearestTarget == nullptr) return;
	CachedMaxWalkSpeed = GetWarriorPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed;
	GetWarriorPlayerCharacterFromActorInfo()->GetCharacterMovement()->MaxWalkSpeed = TargetLockWalkSpeed;
}

void UPlayerAbility_TargetLock::InitMappingContext()
{
	if (CurrentNearestTarget == nullptr) return;
	UEnhancedInputLocalPlayerSubsystem* Subsystem = GetWarriorPlayerControllerFromActorInfo()->GetLocalPlayer()->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(Subsystem);

	Subsystem->AddMappingContext(TargetLockMappingContext, 3);
}

void UPlayerAbility_TargetLock::GetAvailableActorsAroundTarget(TArray<AActor*>& ActorsOnRight,
	TArray<AActor*>& ActorsOnLeft, AActor* TargetActor)
{
	const FVector PlayerLocation = GetWarriorPlayerCharacterFromActorInfo()->GetActorLocation();
	const FVector PlayerToNearestTargetNormalized = (CurrentNearestTarget->GetActorLocation() - PlayerLocation).GetSafeNormal();
	for (AActor* Actor : FoundTargets)
	{
		if (!Actor || Actor == CurrentNearestTarget) continue;
		const FVector PlayerToActorNormalized = (Actor->GetActorLocation() - PlayerLocation).GetSafeNormal();
		FVector CrossValue = FVector::CrossProduct(PlayerToNearestTargetNormalized, PlayerToActorNormalized);
		if (CrossValue.Z >= 0.f)
		{
			ActorsOnRight.AddUnique(Actor);
		}
		else
		{
			ActorsOnLeft.AddUnique(Actor);
		}
	}
}

void UPlayerAbility_TargetLock::FindOtherTarget()
{
	CurrentNearestTarget = nullptr;
	FoundTargets.Empty();

	GetAvailableTargetsToLock();

	if (FoundTargets.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}

	// 가장 가까운 액터 찾기
	CurrentNearestTarget = FindNearestTarget(FoundTargets);
}

void UPlayerAbility_TargetLock::UpdateTargetLockWidgetPosition(float DeltaTime)
{
	if (CurrentNearestTarget == nullptr || UWarriorFunctionLibrary::NativeDoesActorHasTag(GetWarriorPlayerCharacterFromActorInfo(),
		WarriorGameplayTags::Shared_Status_Death))
	{
		CancelTargetLockAbility();
		return;
	}
	if (UWarriorFunctionLibrary::NativeDoesActorHasTag(CurrentNearestTarget, WarriorGameplayTags::Shared_Status_Death))
	{
		FindOtherTarget();
		return;
	}
	else 
	{
		SetTargetLockWidgetPosition();
	}

	if (!UWarriorFunctionLibrary::NativeDoesActorHasTag(GetWarriorPlayerCharacterFromActorInfo(), WarriorGameplayTags::Player_Status_Rolling))
	{
		FRotator LookAtRotator = UKismetMathLibrary::FindLookAtRotation(
		   GetWarriorPlayerCharacterFromActorInfo()->GetActorLocation(),
		   CurrentNearestTarget->GetActorLocation());

		LookAtRotator -= FRotator(TargetLockCameraOffset, 0.f,0.f);

		const FRotator CurrentControllerRot = GetWarriorPlayerControllerFromActorInfo()->GetControlRotation();
		const FRotator DeltaRotator = FMath::RInterpTo(CurrentControllerRot,
			LookAtRotator,DeltaTime, RotationSpeed);

		
	
		GetWarriorPlayerCharacterFromActorInfo()->SetActorRotation(FRotator(0.f, DeltaRotator.Yaw, 0.f));
		GetWarriorPlayerControllerFromActorInfo()->SetControlRotation(FRotator(DeltaRotator.Pitch, DeltaRotator.Yaw, 0.f));
	}
}

void UPlayerAbility_TargetLock::SwitchTarget(const FGameplayTag& SwitchTag)
{
	if (bIsSwitched)
	{
		bIsSwitched = false;
		return;
	} 
	bIsSwitched = true;

	
	FoundTargets.Empty();

	GetAvailableTargetsToLock();

	if (!CurrentNearestTarget || FoundTargets.IsEmpty())
	{
		CancelTargetLockAbility();
		return;
	}
	
	TArray<AActor*> ActorsOnRight;
	TArray<AActor*> ActorsOnLeft;
	GetAvailableActorsAroundTarget(ActorsOnRight, ActorsOnLeft, CurrentNearestTarget);

	AActor* NewNearestActor = nullptr;
	if (SwitchTag.MatchesTagExact(WarriorGameplayTags::Player_Event_SwitchTarget_Left))
	{
		if (!ActorsOnLeft.IsEmpty()) 
			NewNearestActor = FindNearestTarget(ActorsOnLeft);
	}
	else
	{
		if (!ActorsOnRight.IsEmpty()) 
			NewNearestActor = FindNearestTarget(ActorsOnRight);
	}

	if (NewNearestActor != nullptr)
		CurrentNearestTarget = NewNearestActor;

	SetTargetLockWidgetPosition();
}



