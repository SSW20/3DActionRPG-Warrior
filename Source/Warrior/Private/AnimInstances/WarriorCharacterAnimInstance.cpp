// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/WarriorCharacterAnimInstance.h"

#include "Characters/WarriorPlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UWarriorCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AWarriorPlayerCharacter>(TryGetPawnOwner());

	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
}

void UWarriorCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent)
	{
		return;
	}

	// 캐릭터의 수평 이동 속도 계산 ( Z값 제외 )
	GroundSpeed = OwningCharacter->GetVelocity().Size2D();

	// GetCurrentAcceleration() --> 현재 가속도 Vector로 반환
	// SizeSquared2D --> 가속도 벡터의 크기 제곱을 반환 , Why? 제곱근 연산보다 이게 더 빠르다
	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
}
