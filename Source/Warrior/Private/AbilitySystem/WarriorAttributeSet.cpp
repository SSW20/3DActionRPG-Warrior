// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/WarriorAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Components/UI/PawnUIComponent.h"
#include "Components/UI/PlayerUIComponent.h"
#include "Interfaces/PawnUIInterface.h"


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

	if (!CachedPawnUIInterface.IsValid())
	{
		CachedPawnUIInterface = TWeakInterfacePtr<IPawnUIInterface>(Data.Target.GetAvatarActor());
	}

	UPawnUIComponent* PawnUIComponent = CachedPawnUIInterface->GetPawnUIComponent();
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));

		PawnUIComponent->OnHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}
	
	if (Data.EvaluatedData.Attribute == GetCurrentRageAttribute())
	{
		SetCurrentRage(FMath::Clamp(GetCurrentRage(), 0.f, GetMaxRage()));

		if (UPlayerUIComponent* PlayerUIComponent = CachedPawnUIInterface->GetPlayerUIComponent())
		{
			PlayerUIComponent->OnRageChanged.Broadcast(GetCurrentRage() / GetCurrentRage());
		}
	}
	
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float IncomingDamage = GetDamage();
		
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth() - IncomingDamage, 0.f, GetMaxHealth()));

		Debug::Print("Current Target Health", GetCurrentHealth());

		PawnUIComponent->OnHealthChanged.Broadcast(GetCurrentHealth() / GetMaxHealth());
	}

	if (GetCurrentHealth() == 0.f)
	{
		UWarriorFunctionLibrary::AddGameplayTagToActorIfNone(Data.Target.GetAvatarActor(), WarriorGameplayTags::Shared_Status_Death);
	}
}
