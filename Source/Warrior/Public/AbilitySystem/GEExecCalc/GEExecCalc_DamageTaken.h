// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectExecutionCalculation.h"
#include "GEExecCalc_DamageTaken.generated.h"



UCLASS()
class WARRIOR_API UGEExecCalc_DamageTaken : public UGameplayEffectExecutionCalculation
{
	GENERATED_BODY()
public:
	UGEExecCalc_DamageTaken();

	// 이 함수는 Execution Calculation의 핵심으로, Gameplay Effect가 적용될 때 서버에서 실행
	// PostGameplayEffectExecute 함수보다 먼저(이전) 실행
	virtual void Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
		FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const override;
};
