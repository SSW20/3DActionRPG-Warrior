// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/WarriorCharacterBase.h"
#include "WarriorEnemyCharacter.generated.h"

class UWidgetComponent;
class UEnemyUIComponent;
class UEnemyCombatComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorEnemyCharacter : public AWarriorCharacterBase
{
	GENERATED_BODY()
public:
	AWarriorEnemyCharacter();

	FORCEINLINE UEnemyCombatComponent* GetEnemyCombatComponent() const {return EnemyCombatComponent;};

	//~ Begin IPawnCombatInterface.
	virtual UPawnCombatComponent* GetPawnCombatComponent() const override;
	//~ End IPawnCombatInterface

	//~ Begin IPawnUIInterface.
	virtual UPawnUIComponent* GetPawnUIComponent() const override;

	virtual UEnemyUIComponent* GetEnemyUIComponent() const override;
	//~ End IPawnUIInterface
	
protected:
	virtual void BeginPlay() override;
	
#pragma region Component
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UEnemyCombatComponent* EnemyCombatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UEnemyUIComponent* EnemyUIComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Combat", meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* EnemyWidgetComponent;
	
#pragma endregion Component

	//~ Begin APawn Interface.
	virtual void PossessedBy(AController* NewController) override;
	//~ End APawn Interface

	void InitAbiliities();
};
