// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/WarriorPlayerCharacter.h"
#include "WarriorDebugHelper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "WarriorGameplayTags.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"

#include "Components/Combat/PlayerCombatComponent.h"
#include "Components/Input/WarriorInputComponent.h"
#include "DataAssets/Input/WarriorInputConfig.h"
#include "DataAssets/StartUpData/WarriorStartUpDataBase.h"

AWarriorPlayerCharacter::AWarriorPlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SprintArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	//	캐릭터의 몸체가 이동 방향을 따라 자동으로 회전하도록 할건지 
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0,500.f,0.f);
	
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f; //	이동을 멈출 때 감속하는 속도를 제어

	PlayerCombatComponent = CreateDefaultSubobject<UPlayerCombatComponent>("PlayerCombatComponent");
}

void AWarriorPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWarriorPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	checkf(WarriorInputConfig, TEXT("InputDataAsset is Null"));

	// ULocalPlayer는 플레이어와 관련된 로컬 정보(입력, 설정 등)를 관리
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();

	// ULocalPlayer에서 Enhanced Input 시스템을 담당하는 서브시스템을 가져옵
	UEnhancedInputLocalPlayerSubsystem* SubSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	checkf(SubSystem, TEXT("SubSystem is Null"));

	// WarriorInputConfig에 정의된 DefaultMappingContext를 서브시스템에 추가
	SubSystem->AddMappingContext(WarriorInputConfig->DefaultMappingContext, 0);
	
	UWarriorInputComponent* WarriorInputComponent = CastChecked<UWarriorInputComponent>(PlayerInputComponent);
	
	WarriorInputComponent->BindMoveInputAction(WarriorInputConfig, WarriorGameplayTags::InputTag_Move, ETriggerEvent::Triggered,
		this, &AWarriorPlayerCharacter::Input_Move);
	WarriorInputComponent->BindMoveInputAction(WarriorInputConfig, WarriorGameplayTags::InputTag_Look, ETriggerEvent::Triggered,
		this, &AWarriorPlayerCharacter::Input_Look);
	WarriorInputComponent->BindAbilityInputAction(WarriorInputConfig, this, &AWarriorPlayerCharacter::Input_AbilityPressed,
		&AWarriorPlayerCharacter::Input_AbilityReleased);
}

void AWarriorPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// IsValid == 메모리에 로드 되었는지 / IsNull() == 레퍼런스가 있는지
	{
		// 동기적 로딩 
		if (UWarriorStartUpDataBase* LoadData = CharacterStartUpData.LoadSynchronous())
		{
			LoadData->GiveToAbilitySystemComponent(WarriorAbilitySystemComponent);
		}
	}
}

void AWarriorPlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotator(0.f, GetController()->GetControlRotation().Yaw, 0.f);

	// 플레이어가 보고있는 "정면" 을 기준으로 돌리기
	if (MovementVector.Y != 0.f)
	{
		const FVector FowardDirection = MovementRotator.RotateVector(FVector::ForwardVector);
		AddMovementInput(FowardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotator.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AWarriorPlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	if (MovementVector.X != 0.f)
	{
		AddControllerYawInput(-MovementVector.X);
	}
	if (MovementVector.Y != 0.f)
	{
		AddControllerPitchInput(-MovementVector.Y);
	}
}

void AWarriorPlayerCharacter::Input_AbilityPressed(FGameplayTag InputTag)
{
	WarriorAbilitySystemComponent->OnAbilityPressed(InputTag);
}

void AWarriorPlayerCharacter::Input_AbilityReleased(FGameplayTag InputTag)
{
	WarriorAbilitySystemComponent->OnAbilityReleased(InputTag);
}
