// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/UI/EnemyUIComponent.h"

#include "Widgets/WarriorWidgetBase.h"

void UEnemyUIComponent::RegisterWidget(UWarriorWidgetBase* Widget)
{
	DrawnWidgets.AddUnique(Widget);
}

void UEnemyUIComponent::ClearRegisteredWidget()
{
	for (UWarriorWidgetBase* Widget : DrawnWidgets)
	{
		if (Widget)
		{
			Widget->RemoveFromParent();
		}
	}
}
