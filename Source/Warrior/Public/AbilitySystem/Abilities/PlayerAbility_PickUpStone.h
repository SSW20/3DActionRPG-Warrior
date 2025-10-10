// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/WarriorPlayerGameplayAbility.h"
#include "PlayerAbility_PickUpStone.generated.h"

class AWarriorStoneBase;
/**
 * 
 */
UCLASS()
class WARRIOR_API UPlayerAbility_PickUpStone : public UWarriorPlayerGameplayAbility
{
	GENERATED_BODY()
protected:
	// ~ Begin UGameplayAbility Interface 
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	// ~ End UGameplayAbility Interface

	UFUNCTION(BlueprintCallable)
	void SearchStones();

	UFUNCTION(BlueprintCallable)
	void ConsumeStones();
private:
	UPROPERTY(EditDefaultsOnly, Category="PickUp Settings")
	FVector BoxSize = FVector(100);

	UPROPERTY(EditDefaultsOnly, Category="PickUp Settings")
	float SearchDistance = 30.f;

	UPROPERTY(EditDefaultsOnly, Category="PickUp Settings")
	TArray<TEnumAsByte<EObjectTypeQuery>> SearchType;

	UPROPERTY(EditDefaultsOnly, Category="PickUp Settings")
	TArray<AWarriorStoneBase*> CollectedStones;
};
