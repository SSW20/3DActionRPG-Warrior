// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorPlayerGameplayAbility.h"
#include "PlayerAbility_TargetLock.generated.h"

class UInputMappingContext;
class UWarriorWidgetBase;
/**
 * 
 */
UCLASS()
class WARRIOR_API UPlayerAbility_TargetLock : public UWarriorPlayerGameplayAbility
{
	GENERATED_BODY()
public:
	
	// ~ Begin UGameplayAbility Interface 
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface
	
	UFUNCTION(BlueprintCallable)
	void UpdateTargetLockWidgetPosition(float DeltaTime);

	UFUNCTION(BlueprintCallable)
	void SwitchTarget(const FGameplayTag& SwitchTag);
private:
	
	void TryLockOnTarget();
	void GetAvailableTargetsToLock();
	AActor* FindNearestTarget(const TArray<AActor*>& FoundActors);
	void DrawLockWidget();
	void SetTargetLockWidgetPosition();
	void InitCharacterWalkSpeed();
	void InitMappingContext();
	void GetAvailableActorsAroundTarget(TArray<AActor*>& ActorsOnRight, TArray<AActor*>& ActorsOnLeft, AActor* TargetActor);
	void FindOtherTarget();
	
	void CancelTargetLockAbility();
	void CleanUp();
	void ResetCharacterWalkSpeed();
	void ResetMappingContext();
	
	
	
	UPROPERTY(EditAnywhere, Category="Target Lock")
	float DetectionRange = 100.f;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	FVector BoxSize = FVector(2000,2000,300);

	UPROPERTY(EditAnywhere, Category="Target Lock")
	TArray<TEnumAsByte<EObjectTypeQuery>>  ObjectTypesToSearch ;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	bool bDrawDebugType = true;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	TSubclassOf<UWarriorWidgetBase> TargetLockWidgetClass;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	float RotationSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	float TargetLockWalkSpeed = 5.f;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	UInputMappingContext* TargetLockMappingContext;

	UPROPERTY(EditAnywhere, Category="Target Lock")
	float TargetLockCameraOffset = 20.f;
	
	UPROPERTY()
	float CachedMaxWalkSpeed;
	
	UPROPERTY()
	TArray<AActor*> FoundTargets;

	UPROPERTY()
	AActor* CurrentNearestTarget;

	UPROPERTY()
	UWarriorWidgetBase* TargetLockWidget;
	
	UPROPERTY()
	FVector2D WidgetSize = FVector2D::ZeroVector;

	UPROPERTY()
	bool bIsSwitched = false;
};
