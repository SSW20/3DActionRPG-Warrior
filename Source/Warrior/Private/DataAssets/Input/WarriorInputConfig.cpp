// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Input/WarriorInputConfig.h"

const UInputAction* UWarriorInputConfig::FindInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FWarriorInputActionConfig& InputActionConfig : MoveInputActionConfigs)
	{
		if (InputActionConfig.InputTag == InputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
