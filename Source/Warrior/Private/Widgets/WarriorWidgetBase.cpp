// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets/WarriorWidgetBase.h"

#include "Components/UI/PlayerUIComponent.h"
#include "Interfaces/PawnUIInterface.h"

void UWarriorWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(GetOwningPlayerPawn()))
	{
		if (UPlayerUIComponent* PlayerUIComponent = PawnUIInterface->GetPlayerUIComponent())
		{
			BP_PlayerUIComponentInitialized(PlayerUIComponent);
		}
	}
}

void UWarriorWidgetBase::InitEnemyWidget(AActor* EnemyActor)
{
	if (IPawnUIInterface* PawnUIInterface = Cast<IPawnUIInterface>(EnemyActor))
	{
		if (UEnemyUIComponent* EnemyUIComponent = PawnUIInterface->GetEnemyUIComponent())
		{
			BP_EnemyUIComponentInitialized(EnemyUIComponent);
		}
	}
}
