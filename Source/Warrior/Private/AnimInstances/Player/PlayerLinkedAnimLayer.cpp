// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstances/Player/PlayerLinkedAnimLayer.h"

UWarriorPlayerAnimInstance* UPlayerLinkedAnimLayer::GetPlayerAnimInstance() const
{
	return Cast<UWarriorPlayerAnimInstance>(GetOwningComponent()->GetAnimInstance());
}
