// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"


UWarriorAttributeSet::UWarriorAttributeSet()
{
	InitCurrentHealth(1.f);
	InitMaxHealth(1.f);
	InitCurrentRage(1.f);
	InitMaxRage(1.f);
	InitAttackPower(1.f);
	InitDefensePower(1.f);
	InitDamage(1.f);

}

void UWarriorAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));
	}
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float IncomingDamage = GetDamage();
		
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - IncomingDamage, 0.f, GetMaxHealth()));

		Debug::Print("Current Target Health", GetCurrentHealth());
	}

	if (GetCurrentHealth() == 0.f)
	{
		UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Death);
	}
}
