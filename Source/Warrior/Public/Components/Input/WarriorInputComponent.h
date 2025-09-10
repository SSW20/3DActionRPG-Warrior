// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAssets/Input/WarriorInputConfig.h"
#include "WarriorInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()
public:
	
	template<class UserObject, typename CallbackFunc>
	void BindMoveInputAction(const UWarriorInputConfig* InputConfig, const FGameplayTag& InputTag, ETriggerEvent TriggerEvent,
		UserObject* UserObj, CallbackFunc Callback);

	template<class UserObject, typename CallbackFunc>
	void BindAbilityInputAction(const UWarriorInputConfig* InputConfig, UserObject* UserObj, CallbackFunc TriggerCallback, CallbackFunc ReleaseCallBack);
};

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindMoveInputAction(const UWarriorInputConfig* InputConfig, const FGameplayTag& InputTag,
	ETriggerEvent TriggerEvent, UserObject* UserObj, CallbackFunc Callback)
{
	checkf(InputConfig, TEXT("Invalid InputConfig"));

	if (const UInputAction* FoundAction = InputConfig->FindInputActionByTag(InputTag))
	{
		BindAction(FoundAction, TriggerEvent, UserObj, Callback);
	}
}

template <class UserObject, typename CallbackFunc>
void UWarriorInputComponent::BindAbilityInputAction(const UWarriorInputConfig* InputConfig, UserObject* UserObj,
	CallbackFunc TriggerCallback, CallbackFunc ReleaseCallBack)
{
	checkf(InputConfig, TEXT("Invalid InputConfig"));

	for (const FWarriorInputActionConfig& AbilityAction : InputConfig->AbilityInputActionConfigs)
	{
		BindAction(AbilityAction.InputAction, ETriggerEvent::Started, UserObj, TriggerCallback, AbilityAction.InputTag);
		BindAction(AbilityAction.InputAction, ETriggerEvent::Completed, UserObj, ReleaseCallBack, AbilityAction.InputTag);
	}
}
