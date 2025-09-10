// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorCharacterBase.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "AbilitySystem/WarriorAttributeSet.h"

// Sets default values
AWarriorCharacterBase::AWarriorCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	WarriorAbilitySystemComponent = CreateDefaultSubobject<UWarriorAbilitySystemComponent>("WarriorAbilitySystemComponent");
	WarriorAttributeSet = CreateDefaultSubobject<UWarriorAttributeSet>("WarriorAttributeSet");
}

void AWarriorCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (WarriorAbilitySystemComponent)
	{
		WarriorAbilitySystemComponent->InitAbilityActorInfo(this,this);

		ensure(!CharacterStartUpData.IsNull());
	}
}

UAbilitySystemComponent* AWarriorCharacterBase::GetAbilitySystemComponent() const
{
	return GetWarriorAbilitySystemComponent();
}


