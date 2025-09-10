// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "Characters/WarriorCharacterBase.h"
#include "WarriorPlayerCharacter.generated.h"

class UPlayerCombatComponent;
class UWarriorInputComponent;
class UWarriorInputConfig;
class UCameraComponent;
class USpringArmComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorPlayerCharacter : public AWarriorCharacterBase
{
	GENERATED_BODY()
public:
	AWarriorPlayerCharacter();
	
protected:
	virtual void BeginPlay() override;
	//어떤 키를 눌렀을 때 어떤 행동을 할지를 정해주는 입력 설정 담당자
	//무슨 키/버튼을 눌렀을 때 (입력 이벤트) 어떤 행동 이름표(InputAction) 를 실행하고 실제로 어떤 함수를 호출해서 게임에서 반응할지를 미리 약속 해두는 곳
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface
private:
#pragma region Components

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UPlayerCombatComponent* PlayerCombatComponent;
#pragma endregion Components

#pragma region EnhancedInput
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Warrior Input", meta = (AllowPrivateAccess = "true"))
	UWarriorInputConfig* WarriorInputConfig;

	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Look(const FInputActionValue& InputActionValue);

	void Input_AbilityPressed(FGameplayTag InputTag);
	void Input_AbilityReleased(FGameplayTag InputTag);
#pragma endregion EnhancedInput

public:
	FORCEINLINE UPlayerCombatComponent* GetPlayerCombatComponent() const { return PlayerCombatComponent; }
	
};
