// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GenericTeamAgentInterface.h"
#include "GameFramework/PlayerController.h"
#include "WarriorPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()
public:
	AWarriorPlayerController();

	virtual FGenericTeamId GetGenericTeamId() const override;

private:
	FGenericTeamId PlayerGenericTeamId;
};
