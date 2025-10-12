// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "WarriorGameModeBase.generated.h"

enum class EWarriorGameModeDifficulty : uint8;
/**
 * 
 */
UCLASS()
class WARRIOR_API AWarriorGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	AWarriorGameModeBase();
	
	FORCEINLINE EWarriorGameModeDifficulty GetCurrentGameDifficulty() const { return CurrentGameDifficulty;}
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Game Difficulty")
	EWarriorGameModeDifficulty CurrentGameDifficulty;

	
};
