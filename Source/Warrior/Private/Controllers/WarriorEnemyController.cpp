// Fill out your copyright notice in the Description page of Project Settings.


#include "Controllers/WarriorEnemyController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

/*	초기화 목록(Initializer List). 부모 클래스인 AAIController의 생성자를 호출. 
	AAIController는 기본적으로 UPathFollowingComponent를 사용하여 경로를 추적합니다.
	SetDefaultSubobjectClass 함수를 사용해서,  AAIController가 사용하는 "PathFollowingComponent"라는 이름의 기본 컴포넌트를
	UCrowdFollowingComponent로 재정의(Override)합니다.

	UCrowdFollowingComponent는 일반적인 경로 추적 기능 외에 복잡한 군중 이동(Crowd Navigation)을 처리하는 데 특화된 컴포넌트입니다.
	즉, 여러 적이 서로 부딪히지 않고 자연스럽게 이동할 수 있도록 도와줍니다.*/

AWarriorEnemyController::AWarriorEnemyController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");

	// 적 진영 = 감지 , 아군 / 중립 진영 = 감지 하지 않음
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;

	// 시야 범위 5000.f , LoseSightRadius = 0 일 경우 감지된 대상을 놓치지 않음 , 시야각 360도
	AISenseConfig_Sight->SightRadius = 5000.f;
	AISenseConfig_Sight->LoseSightRadius = 0.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 360.f;
	
	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>("EnemyPerceptionComponent");

	// 위에 시야 설정을 적용
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);

	// 주요 감지 기능을 시야 기능으로 설정
	EnemyPerceptionComponent->SetDominantSense(UAISenseConfig_Sight::StaticClass());

	// 대상을 감지하거나 놓쳤을 때의 콜백함수
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this,&ThisClass::OnEnemyPerceptionUpdated);

	// Team Id 정하기
	SetGenericTeamId(FGenericTeamId(1));
}

void AWarriorEnemyController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (Actor && Stimulus.WasSuccessfullySensed())
	{
		if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
		{
			BlackboardComponent->SetValueAsObject("TargetActor", Actor);
		}
	}
}

// 감지한 Actor의 Team ID가 다르면 Hostile(적)을 반환 아닐시 Friend 를 반환
ETeamAttitude::Type AWarriorEnemyController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* OtherPawn = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<IGenericTeamAgentInterface>(OtherPawn->GetController());

	if (OtherTeamAgent && OtherPawn)
	{
		return OtherTeamAgent->GetGenericTeamId() != GetGenericTeamId() ? ETeamAttitude::Hostile : ETeamAttitude::Friendly;
	}
	return ETeamAttitude::Neutral;
}

void AWarriorEnemyController::BeginPlay()
{
	Super::BeginPlay();

	if (UCrowdFollowingComponent* PathComp = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		PathComp->SetCrowdSimulationState(bEnableDetourAvoidance? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);

		switch (DetourAvoidanceQuality)
		{
		case 1:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low); break;
		case 2:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium); break;
		case 3:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good); break;
		case 4:
			PathComp->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High); break;
		default: break;
		}

		PathComp->SetAvoidanceGroup(1);
		PathComp->SetGroupsToAvoid(1);
		PathComp->SetCrowdCollisionQueryRange(DetourAvoidanceRange);
	}
}
