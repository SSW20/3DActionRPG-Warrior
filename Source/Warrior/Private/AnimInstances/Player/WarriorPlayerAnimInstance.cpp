// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/WarriorPlayerAnimInstance.h"

#include "Characters/WarriorPlayerCharacter.h"

void UWarriorPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningCharacter)
	{
		OwningPlayerCharacter = Cast<AWarriorPlayerCharacter>(OwningCharacter);
	}
}

void UWarriorPlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (GroundSpeed > 0.f)
	{
		ElapsedTime = 0.f;
		bRelaxed = false;
	}
	else
	{
		ElapsedTime += DeltaSeconds;
		bRelaxed = ElapsedTime >= RelaxThreshold;
	}
	
}
