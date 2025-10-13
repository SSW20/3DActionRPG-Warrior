// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/GameInstance.h"
#include "WarriorGameInstance.generated.h"

struct FGameplayTag;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FWarriorMapInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, Category="Map Info")
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditDefaultsOnly, Category="Map Info")
	FGameplayTag LevelTag;
};

UCLASS()
class WARRIOR_API UWarriorGameInstance : public UGameInstance
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Map Info")
	TArray<FWarriorMapInfo> MapInfos;

	virtual void OnPreLoadMap(const FString& MapName);
	virtual void OnDestinationWorldLoaded(UWorld* LoadedWorld);

	// UUserWidget 클래스의 서브클래스 포인터를 담을 변수를 선언합니다.
	UPROPERTY(EditDefaultsOnly, Category = "Loading Screen")
	TSubclassOf<UUserWidget> CustomLoadingScreenWidgetClass; 
public:
	UFUNCTION(BlueprintPure)
	TSoftObjectPtr<UWorld> GetMapByTag(FGameplayTag Tag) const;

	virtual void Init() override;
};
