// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarriorWidgetBase.generated.h"

class UEnemyUIComponent;
class UPlayerUIComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorWidgetBase : public UUserWidget
{
	GENERATED_BODY()
protected:
	// 위젯이 생성된 후 호출 
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnPlayerUIComponentInitialized"))
	void BP_PlayerUIComponentInitialized(UPlayerUIComponent* PlayerUIComponent); 

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnEnemyUIComponentInitialized"))
	void BP_EnemyUIComponentInitialized(UEnemyUIComponent* EnemyUIComponent); 
	
public:
	UFUNCTION(BlueprintCallable)
	void InitEnemyWidget(AActor* EnemyActor);
};
