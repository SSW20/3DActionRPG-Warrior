// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/GEExecCalc/GEExecCalc_DamageTaken.h"
#include "AbilitySystem/WarriorAttributeSet.h"
#include "WarriorDebugHelper.h"
#include "WarriorGameplayTags.h"

struct FWarriorDamageCapture
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower)
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage)


	FWarriorDamageCapture()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,AttackPower,Source,false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,DefensePower,Target,false)
		DEFINE_ATTRIBUTE_CAPTUREDEF(UWarriorAttributeSet,Damage,Source,false)
	}
};

static const FWarriorDamageCapture& GetWarriorDamageCapture()
{
	static FWarriorDamageCapture WarriorDamageCapture;
	return WarriorDamageCapture;
}

UGEExecCalc_DamageTaken::UGEExecCalc_DamageTaken()
{
	/*Slow way of doing capture*/
	//FProperty* AttackPowerProperty = FindFieldChecked<FProperty>(
	//	UWarriorAttributeSet::StaticClass(),
	//	GET_MEMBER_NAME_CHECKED(UWarriorAttributeSet,AttackPower)
	//);

	//FGameplayEffectAttributeCaptureDefinition AttackPowerCaptureDefinition(
	//	AttackPowerProperty,
	//	EGameplayEffectAttributeCaptureSource::Source,
	//	false
	//);

	//RelevantAttributesToCapture.Add(AttackPowerCaptureDefinition);

	
	// 매크로
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetWarriorDamageCapture().DamageDef);

}

void UGEExecCalc_DamageTaken::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	// ExecutionParams: GE 실행에 필요한 모든 입력 정보 (소스, 타겟, GE 스펙 등)를 담고 있는 구조체.
	// OutExecutionOutput: 계산된 최종 결과를 GAS 시스템에 전달하여 능력치를 실제로 변경하는 데 사용되는 출력 구조체

	// // ExecutionParams을 통해 ASC를 가져옴 
	// const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	// const UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();
	//
	// // ASC를 가져오면 ASC를 가지는 액터를 가져올 수 있음
	// AActor* SourceActor =  SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	// AActor* TargetActor = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	//ExecutionParams을 통해 GameplayEffectSpec(GE의 설계도)을 가져옴 
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	//EffectSpec에서 Source와 Target에 붙어 있는 Gameplay Tag들을 가져옴
	const FGameplayTagContainer* SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();
	
	//능력치 평가에 필요한 파라미터 구조체인 FAggregatorEvaluateParameters를 초기화
	//능력치 값을 평가할 때 소스/타겟 태그의 영향을 고려
	FAggregatorEvaluateParameters EvaluateParams;
	EvaluateParams.SourceTags = SourceTags;
	EvaluateParams.TargetTags = TargetTags;

	FGameplayEffectContextHandle EffectContextHandle = EffectSpec.GetContext();

	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().AttackPowerDef,EvaluateParams, SourceAttackPower);
	
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetWarriorDamageCapture().DefensePowerDef,EvaluateParams, TargetDefensePower);

	float BaseDamage = 0.f;
	float LightComboCount = 0.f;
	float HeavyComboCount = 0.f;
	for (const TPair<FGameplayTag, float>& TagsToValue : EffectSpec.SetByCallerTagMagnitudes)
	{
		if (TagsToValue.Key.MatchesTagExact(WarriorGameplayTags::Shared_SetByCaller_BaseDamage))
		{
			BaseDamage = TagsToValue.Value;
		}
		else if (TagsToValue.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Light))
		{
			LightComboCount = TagsToValue.Value;
			
		}
		else if (TagsToValue.Key.MatchesTagExact(WarriorGameplayTags::Player_SetByCaller_AttackType_Heavy))
		{
			HeavyComboCount = TagsToValue.Value;
		}
	}

	if (LightComboCount > 0.f)
	{
		BaseDamage *=  (LightComboCount - 1.f) * 0.1 + 1.f;
	}
	if (HeavyComboCount > 0.f)
	{
		BaseDamage *=  (HeavyComboCount - 1.f) * 0.2 + 1.f;
	}
	float TotalDamage = BaseDamage * SourceAttackPower / TargetDefensePower;
	
	Debug::Print("Total Damage Amount : ", TotalDamage);

	//계산된 결과를 어떻게 적용할지 설정  
	//OutExecutionOutput은 자동으로 Target의 AbilitySystemComponent에 대한 변경 지시를 담는 '컨테이너' 역할을 함
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(
		UWarriorAttributeSet::GetDamageAttribute(),
		EGameplayModOp::Override,
		TotalDamage));
}
