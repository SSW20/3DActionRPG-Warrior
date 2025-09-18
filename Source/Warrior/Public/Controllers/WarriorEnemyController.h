// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "WarriorEnemyController.generated.h"

class UAISenseConfig_Sight;
struct FAIStimulus;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorEnemyController : public AAIController
{
	GENERATED_BODY()
public:
	/*
	 *	FObjectInitializer는 언리얼 오브젝트가 생성될 때 초기화 데이터를 전달하는 데 사용되는 구조체
	 *	이를 통해 부모 클래스(AAIController)의 속성을 초기화하거나 기본 하위 컴포넌트를 설정할 수 있습니다.*/
	AWarriorEnemyController(const FObjectInitializer& ObjectInitializer);

	/*	AI 감지 컴포넌트, 이 컴포넌트가 AI의 시야, 청각 등 모든 감지 기능을 총괄 */
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAIPerceptionComponent* EnemyPerceptionComponent;

	/*	시야 감지 설정 컴포넌트, AI가 "시각"으로 대상을 어떻게 감지할지 구체적인 설정을 담는 역할*/
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UAISenseConfig_Sight* AISenseConfig_Sight;

	// AI 감지 컴포넌트 에서의 콜백 함수
	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

	// ~ Begin IGenericTeamAgentInterface
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	// ~ End IGenericTeamAgentInterface

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly , Category = "Detour Crowd Avoidance Config")
	bool bEnableDetourAvoidance = true;

	UPROPERTY(EditDefaultsOnly , Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourAvoidance", UIMIN = "1", UIMAX = "4"))
	int32 DetourAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly , Category = "Detour Crowd Avoidance Config", meta = (EditCondition = "bEnableDetourAvoidance"))
	float DetourAvoidanceRange = 600.f;
};	 
