// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorEnemyCharacter.h"

#include "WarriorDebugHelper.h"
#include "Components/WidgetComponent.h"
#include "Components/Combat/EnemyCombatComponent.h"
#include "Components/UI/EnemyUIComponent.h"
#include "DataAssets/StartUpData/WarriorStartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFrameWork/CharacterMovementComponent.h"
#include "Widgets/WarriorWidgetBase.h"

AWarriorEnemyCharacter::AWarriorEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0, 180.f, 0);
	GetCharacterMovement()->MaxWalkSpeed = 300.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyCombatComponent = CreateDefaultSubobject<UEnemyCombatComponent>("EnemyCombatComponent");
	EnemyUIComponent = CreateDefaultSubobject<UEnemyUIComponent>("EnemyUIComponent");
	EnemyWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("EnemyWidgetComponent");

	EnemyWidgetComponent->SetupAttachment(GetMesh());

}

UPawnCombatComponent* AWarriorEnemyCharacter::GetPawnCombatComponent() const
{
	return  EnemyCombatComponent;
}

UPawnUIComponent* AWarriorEnemyCharacter::GetPawnUIComponent() const
{
	return EnemyUIComponent;
}

UEnemyUIComponent* AWarriorEnemyCharacter::GetEnemyUIComponent() const
{
	return EnemyUIComponent;
}

void AWarriorEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyWidgetComponent)
	{
		Cast<UWarriorWidgetBase>(EnemyWidgetComponent->GetWidget())->InitEnemyWidget(this);
	}
}

void AWarriorEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbiliities();
}

void AWarriorEnemyCharacter::InitAbiliities()
{
	// IsValid == 메모리에 로드 되었는지 / IsNull() == 레퍼런스가 있는지
	
		// 비동기적 로딩 
		UAssetManager::GetStreamableManager().RequestAsyncLoad(CharacterStartUpData.ToSoftObjectPath(), FStreamableDelegate::CreateLambda(
			[this]()
			{
				if (UWarriorStartUpDataBase* StartupData = CharacterStartUpData.Get())
				{
					StartupData->GiveToAbilitySystemComponent(GetWarriorAbilitySystemComponent(), 1);

					Debug::Print(FString("Successful Asynchronous Loaded!"));
				}
			}));
}
