// Fill out your copyright notice in the Description page of Project Settings.


#include "Gamemodes/WarriorSurvivalGameMode.h"

#include "NavigationSystem.h"
#include "Characters/WarriorEnemyCharacter.h"
#include "Engine/AssetManager.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"



void AWarriorSurvivalGameMode::BeginPlay()
{
	checkf(WaveSpawnerDataTable, TEXT("Data Table Is Missing :("));
	Super::BeginPlay();
	
	SetSurvivalGameModeState(ESurvivalGameModeState::WaitSpawnNewWave);

	TotalWavesToSpawn = WaveSpawnerDataTable->GetRowNames().Num();
	PreLoadEnemies();
}

void AWarriorSurvivalGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// 새로운 웨이브 시작 전 쉬는 타임
	if (CurrentGameModeState == ESurvivalGameModeState::WaitSpawnNewWave)
	{
		// 카운트 세기  < 완
		TimeSpendSinceStart += DeltaSeconds;
		
		if (TimeSpendSinceStart >= WaitTimeNewWaveThreshold)
		{
			SetSurvivalGameModeState(ESurvivalGameModeState::SpawningNewWave);
			TimeSpendSinceStart = 0.f;
		}
		// 웨이브 스타트 UI 올리기
	}

	// 웨이브 시작 하는 카운트 다운
	if (CurrentGameModeState == ESurvivalGameModeState::SpawningNewWave)
	{
		TimeSpendSinceStart += DeltaSeconds;

		if (TimeSpendSinceStart >= EnemySpawnTimeThreshold)
		{
			// 적 생성
			CurrentSpawnCountThisWave += SpawnWaveEnemies();
			
			TimeSpendSinceStart = 0.f;

			SetSurvivalGameModeState(ESurvivalGameModeState::InProgress);
		}
	}

	// 웨이브가 끝났을 시
	if (CurrentGameModeState == ESurvivalGameModeState::WaveComplete)
	{
		TimeSpendSinceStart += DeltaSeconds;
		if (TimeSpendSinceStart >= WaitTimeWaveCompleteThreshold)
		{
			TimeSpendSinceStart = 0.f;

			CurrentWaveCount++;

			if (IsAllWavesDone())
			{
				SetSurvivalGameModeState(ESurvivalGameModeState::AllWavesComplete);
			}
			else
			{
				SetSurvivalGameModeState(ESurvivalGameModeState::WaitSpawnNewWave);
				PreLoadEnemies();
			}
		}
	}
}

void AWarriorSurvivalGameMode::SetSurvivalGameModeState(ESurvivalGameModeState NewGameState)
{
	CurrentGameModeState = NewGameState;
	OnGameModeStateChanged.Broadcast(CurrentGameModeState);
}

bool AWarriorSurvivalGameMode::IsAllWavesDone()
{
	return TotalWavesToSpawn < CurrentWaveCount;
}

bool AWarriorSurvivalGameMode::ShouldStopSpawning()
{
	return TotalSpawnCountThisWave >= GetEnemySpawnerInfoTableRow()->TotalEnemiesToSpawn;
}

FWarriorEnemySpawnerInfoTableRow* AWarriorSurvivalGameMode::GetEnemySpawnerInfoTableRow()
{
	const FName RowName = FName(TEXT("Wave") + FString::FromInt(CurrentWaveCount));
	FWarriorEnemySpawnerInfoTableRow* FoundRow = WaveSpawnerDataTable->FindRow<FWarriorEnemySpawnerInfoTableRow>(RowName,FString());
	checkf(FoundRow, TEXT("Invalid Found Row in Data Table"));
	return FoundRow;
}

void AWarriorSurvivalGameMode::PreLoadEnemies()
{
	if (IsAllWavesDone())
	{
		return;
	}

	PreLoadedEnemyClassMap.Empty();
	
	for (FWarriorEnemySpawnerInfo& SpawnInfo : GetEnemySpawnerInfoTableRow()->SpawnInfos)
	{
		UAssetManager::GetStreamableManager().RequestAsyncLoad(SpawnInfo.EnemyCharacterClassToSpawn.ToSoftObjectPath(),
			FStreamableDelegate::CreateLambda([this, SpawnInfo]()
			{
				if (UClass* EnemyClass = SpawnInfo.EnemyCharacterClassToSpawn.Get())
				{
					PreLoadedEnemyClassMap.Emplace(SpawnInfo.EnemyCharacterClassToSpawn,EnemyClass);
				}
			}));
	}
}

int32 AWarriorSurvivalGameMode::SpawnWaveEnemies()
{
	if (SpawnPoints.IsEmpty())
	{
		UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), SpawnPoints);
	}

	checkf(!SpawnPoints.IsEmpty(), TEXT("SpawnPoints is empty"));

	int32 EnemiesSpawnCountThisTime = 0;
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (FWarriorEnemySpawnerInfo& SpawnInfo : GetEnemySpawnerInfoTableRow()->SpawnInfos)
	{
		if (SpawnInfo.EnemyCharacterClassToSpawn.IsNull()) continue;

		const int32 SpawnCount = FMath::RandRange(SpawnInfo.MinSpawnCount, SpawnInfo.MaxSpawnCount);

		UClass* EnemyClass = PreLoadedEnemyClassMap.FindChecked(SpawnInfo.EnemyCharacterClassToSpawn);
		
		for (int32 i = 0; i < SpawnCount; i++)
		{
			const int32 RandomSpawnPointIdx = FMath::RandRange(0, SpawnPoints.Num() - 1);
			const FVector SpawnOrigin = SpawnPoints[RandomSpawnPointIdx]->GetActorLocation();
			const FRotator SpawnRotation = SpawnPoints[RandomSpawnPointIdx]->GetActorForwardVector().ToOrientationRotator();

			FVector SpawnLocation;
			UNavigationSystemV1::K2_GetRandomLocationInNavigableRadius(this, SpawnOrigin, SpawnLocation, 300.f);
			SpawnLocation += FVector(0,0,150.f);

			AWarriorEnemyCharacter* SpawnedEnemy = GetWorld()->SpawnActor<AWarriorEnemyCharacter>(EnemyClass, SpawnLocation, SpawnRotation, SpawnParameters);

			if (SpawnedEnemy)
			{
				SpawnedEnemy->OnDestroyed.AddDynamic(this, &ThisClass::OnEnemyDestroyed);
				EnemiesSpawnCountThisTime++;
				TotalSpawnCountThisWave++;
			}
			if (ShouldStopSpawning())
			{
				return EnemiesSpawnCountThisTime;
			}
		}
	}
	return EnemiesSpawnCountThisTime;
}

void AWarriorSurvivalGameMode::OnEnemyDestroyed(AActor* DestroyedActor)
{
	CurrentSpawnCountThisWave--;
	if (!ShouldStopSpawning())
	{
		CurrentSpawnCountThisWave += SpawnWaveEnemies();
	}
	else if (CurrentSpawnCountThisWave == 0)
	{
		TotalSpawnCountThisWave = 0;
		SetSurvivalGameModeState(ESurvivalGameModeState::WaveComplete);
	}
}


void AWarriorSurvivalGameMode::RegisterSpawnedEnemies(const TArray<AActor*>& SpawnedEnemies)
{
	for (AActor* SpawnActor : SpawnedEnemies)
	{
		SpawnActor->OnDestroyed.AddDynamic(this, &ThisClass::OnEnemyDestroyed);
		CurrentSpawnCountThisWave++;
	}
}