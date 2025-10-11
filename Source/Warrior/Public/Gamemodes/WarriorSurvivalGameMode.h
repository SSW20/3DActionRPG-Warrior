// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Gamemodes/WarriorGameModeBase.h"
#include "WarriorSurvivalGameMode.generated.h"


class AWarriorEnemyCharacter;
/**
 * 
 */
UENUM(BlueprintType)
enum class ESurvivalGameModeState : uint8
{
	WaitSpawnNewWave,
	SpawningNewWave,
	InProgress,
	WaveComplete,
	AllWavesComplete,
	PlayerDied
};

USTRUCT(BlueprintType)
struct FWarriorEnemySpawnerInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AWarriorEnemyCharacter> EnemyCharacterClassToSpawn;

	UPROPERTY(EditAnywhere)
	int32 MinSpawnCount = 1;

	UPROPERTY(EditAnywhere)
	int32 MaxSpawnCount = 3;
};

USTRUCT(BlueprintType)
struct FWarriorEnemySpawnerInfoTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FWarriorEnemySpawnerInfo> SpawnInfos;

	UPROPERTY(EditAnywhere)
	int32 TotalEnemiesToSpawn = 1;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameModeStateChanged, ESurvivalGameModeState, GameModeState);


UCLASS()
class WARRIOR_API AWarriorSurvivalGameMode : public AWarriorGameModeBase
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedEnemies(const TArray<AActor*>& SpawnedEnemies);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	void SetSurvivalGameModeState(ESurvivalGameModeState NewGameState);
	bool IsAllWavesDone();
	bool ShouldStopSpawning();
	FWarriorEnemySpawnerInfoTableRow* GetEnemySpawnerInfoTableRow();
	void PreLoadEnemies();
	int32 SpawnWaveEnemies();

	UFUNCTION()
	void OnEnemyDestroyed(AActor* DestroyedActor);
private:
	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FOnGameModeStateChanged OnGameModeStateChanged;

	UPROPERTY()
	ESurvivalGameModeState CurrentGameModeState;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="WaveInfo")
	UDataTable* WaveSpawnerDataTable;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="WaveInfo")
	int32 TotalWavesToSpawn;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="WaveInfo")
	int32 CurrentWaveCount = 1;

	UPROPERTY()
	float TimeSpendSinceStart = 0.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="WaveInfo")
	float WaitTimeNewWaveThreshold = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="WaveInfo")
	float EnemySpawnTimeThreshold = 2.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(AllowPrivateAccess=true), Category="WaveInfo")
	float WaitTimeWaveCompleteThreshold = 5.f;
	
	UPROPERTY()
	TMap<TSoftClassPtr<AWarriorEnemyCharacter>,UClass*> PreLoadedEnemyClassMap;
	
	UPROPERTY()
	TArray<AActor*> SpawnPoints;

	UPROPERTY()
	int32 CurrentSpawnCountThisWave = 0;

	UPROPERTY()
	int32 TotalSpawnCountThisWave = 0;
};
