// Fill out your copyright notice in the Description page of Project Settings.


#include "WarriorFunctionLibrary.h"

#include <functional>

#include "AbilitySystemBlueprintLibrary.h"
#include "GenericTeamAgentInterface.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Interfaces/PawnCombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

UWarriorAbilitySystemComponent* UWarriorFunctionLibrary::GetWarriorAbilitySystemComponentFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UWarriorAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));
}

void UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTag)
{
	UWarriorAbilitySystemComponent* WarriorASC = GetWarriorAbilitySystemComponentFromActor(InActor);
	if (WarriorASC)
	{
		WarriorASC->AddLooseGameplayTag(InTag);
	}
}

void UWarriorFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag InTag)
{
	UWarriorAbilitySystemComponent* WarriorASC = GetWarriorAbilitySystemComponentFromActor(InActor);
	if (WarriorASC)
	{
		WarriorASC->RemoveLooseGameplayTag(InTag);
	}
}

bool UWarriorFunctionLibrary::NativeDoesActorHasTag(AActor* InActor, FGameplayTag InTag)
{
	UWarriorAbilitySystemComponent* ASC = GetWarriorAbilitySystemComponentFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(InTag))
	{
		return ASC->HasMatchingGameplayTag(InTag);
	}
	return false;
}

bool UWarriorFunctionLibrary::BP_DoesActorHaveTag(AActor* InActor, FGameplayTag InTag)
{
	return NativeDoesActorHasTag(InActor, InTag);
}

UPawnCombatComponent* UWarriorFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (InActor->Implements<UPawnCombatInterface>())
	{
		IPawnCombatInterface* CombatInterface = Cast<IPawnCombatInterface>(InActor);
		return CombatInterface->GetPawnCombatComponent();
	}
	return nullptr;
}

UPawnCombatComponent* UWarriorFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor)
{
	return NativeGetPawnCombatComponentFromActor(InActor);
}

bool UWarriorFunctionLibrary::IsTargetHostile(APawn* OwningPawn, APawn* TargetPawn)
{
	IGenericTeamAgentInterface* OwningTeamAgent = Cast<IGenericTeamAgentInterface>(OwningPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (OwningTeamAgent && TargetTeamAgent)
	{
		return OwningTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}
	return false;
}

float UWarriorFunctionLibrary::GetScalableFloatByLevel(const FScalableFloat& RollingDistance, const float Level)
{
	return RollingDistance.GetValueAtLevel(Level);
}

FGameplayTag UWarriorFunctionLibrary::GetHitReactDirection(AActor* DamagedActor, AActor* HitActor,
	float& OutAngle)
{
	const FVector DamagedForward = DamagedActor->GetActorForwardVector();
	const FVector ToHitActorNormalized = (HitActor->GetActorLocation() - DamagedActor->GetActorLocation()).GetSafeNormal();

	const float DotValue = FVector::DotProduct(DamagedForward, ToHitActorNormalized);
	OutAngle = UKismetMathLibrary::DegAcos(DotValue);

	// 기존의 벡터 외적은 오른손 법칙을 따라가지만 언리얼의 외적은 왼손을 따라감
	// 기존 방향의 오른쪽 --> 양수 / 기존 방향의 왼쪽 --> 음수
	const FVector CrossValue = FVector::CrossProduct(DamagedForward, ToHitActorNormalized);
	if (CrossValue.Z  < 0.f)
	{
		OutAngle = -OutAngle;
	}

	if (OutAngle <= 45.f && OutAngle >= -45.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Front;
	}
	if (OutAngle <= 135.f && OutAngle >= 45.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Right;
	}
	if (OutAngle <= -135.f || OutAngle >= 135.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Back;
	}
	if (OutAngle <= -45.f && OutAngle >= -135.f)
	{
		return WarriorGameplayTags::Shared_Status_HitReact_Left;
	}
	return FGameplayTag();
}

bool UWarriorFunctionLibrary::IsBlocked(const AActor* Attacker,const AActor* Defender)
{
	const float DotVal = FVector::DotProduct(Attacker->GetActorForwardVector(), Defender->GetActorForwardVector());
	return DotVal < -0.6f;
}

bool UWarriorFunctionLibrary::ApplyEffectSpecHandleToActor(AActor* ThisActor, AActor* OtherActor,
	const FGameplayEffectSpecHandle& SpecHandle)
{
	UWarriorAbilitySystemComponent* ThisASC = GetWarriorAbilitySystemComponentFromActor(ThisActor);
	UWarriorAbilitySystemComponent* OtherASC = GetWarriorAbilitySystemComponentFromActor(OtherActor);
	
	FActiveGameplayEffectHandle ActiveSpecHandle = ThisASC->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, OtherASC);
	return ActiveSpecHandle.WasSuccessfullyApplied();
}

void UWarriorFunctionLibrary::CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval,
	float& OutRemainingTime, EWarriorCountDownActionInput CountDownInput,
	EWarriorCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo)
{
}
