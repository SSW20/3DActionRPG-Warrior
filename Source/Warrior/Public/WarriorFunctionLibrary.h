// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "WarriorGameInstance.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "WarriorTypes/WarriorEnumTypes.h"
#include "WarriorFunctionLibrary.generated.h"

struct FGameplayEffectSpecHandle;
struct FGameplayAbilitySpecHandle;
struct FScalableFloat;
class UPawnCombatComponent;
class UWarriorAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class WARRIOR_API UWarriorFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	static UWarriorAbilitySystemComponent* GetWarriorAbilitySystemComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable)
	static void AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable)
	static void RemoveGameplayTagFromActorIfFound(AActor* InActor,FGameplayTag InTag);
	
	static bool NativeDoesActorHasTag(AActor* InActor, FGameplayTag InTag);
	
	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Does Actor Have Tag"))
	static bool BP_DoesActorHaveTag(AActor* InActor,FGameplayTag InTag);

	static UPawnCombatComponent* NativeGetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get PawnCombatComponent From Actor"))
	static UPawnCombatComponent* BP_GetPawnCombatComponentFromActor(AActor* InActor);

	UFUNCTION(BlueprintPure)
	static bool IsTargetHostile(APawn* OwningPawn, APawn* TargetPawn);

	UFUNCTION(BlueprintPure)
	static float GetScalableFloatByLevel(const FScalableFloat& RollingDistance, const float Level);

	UFUNCTION(BlueprintCallable)
	static FGameplayTag GetHitReactDirection(AActor* DamagedActor, AActor* HitActor,float& OutAngle);

	static bool IsBlocked(const AActor* Attacker,const AActor* Defender);

	UFUNCTION()
	static bool ApplyEffectSpecHandleToActor(AActor* ThisActor, AActor* OtherActor,const FGameplayEffectSpecHandle& SpecHandle);

	// Custom Latent 뼈대 만들기
	// ExpandEnumAsExecs == enum 블루프린트 노드에서 **여러 개의 개별적인 실행 핀(Execution Pins, Exec Pins)으로 자동으로 확장하도록 언리얼 엔진에게 지시하는 역할
	UFUNCTION(BlueprintCallable, meta =(Latent, WorldContext="WorldContextObject", LatentInfo="LatentInfo",
		ExpandEnumAsExecs = "CountDownInput|CountDownOutput", TotalTime = "1.0", UpdateInterval = "0.1"))
	static void CountDown(const UObject* WorldContextObject, float TotalTime, float UpdateInterval, float& OutRemainingTime,
		EWarriorCountDownActionInput CountDownInput, EWarriorCountDownActionOutput& CountDownOutput, FLatentActionInfo LatentInfo, bool bReverse);

	UFUNCTION(BlueprintPure, meta = (WorldContext= "WorldContextObject"))
	static UWarriorGameInstance* GetWarriorGameInstance(const UObject* WorldContextObject);

	UFUNCTION(BlueprintCallable, meta = (WorldContext= "WorldContextObject"))
	static void SetWarriorInputMode(const UObject* WorldContextObject, EWarriorInputMode InputMode);

	UFUNCTION(BlueprintCallable)
	static void SaveCurrentGameModeDifficulty(EWarriorGameModeDifficulty Difficulty);

	UFUNCTION(BlueprintCallable)
	static bool LoadCurrentGameModeDifficulty(EWarriorGameModeDifficulty& OutDifficulty);
};
