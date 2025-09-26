// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayAbilitySpecHandle.h"
#include "GameplayEffectTypes.h"
#include "GameFramework/Actor.h"
#include "WarriorProjectileBase.generated.h"

struct FGameplayEventData;
struct FGameplayAbilitySpecHandle;
class UNiagaraComponent;
class UProjectileMovementComponent;
class UBoxComponent;

UENUM(BlueprintType)
enum class FProjectileCollisionPolicy : uint8
{
	
	OnHit,
	OnOverlapped
};

UCLASS()
class WARRIOR_API AWarriorProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarriorProjectileBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UBoxComponent* BoxComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UNiagaraComponent* NiagaraComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	FProjectileCollisionPolicy CollisionPolicy = FProjectileCollisionPolicy::OnHit; 

	UPROPERTY(BlueprintReadOnly, Category = "Projectile", meta=(ExposeOnSpawn="true"))
	FGameplayEffectSpecHandle DamageEffectSpecHandle;
	
	UFUNCTION(BlueprintImplementableEvent)
	void ProjectileHit(const FVector& ImpactPoint);

	UFUNCTION()
	virtual void HandleApplyProjectileDamage(AActor* OtherActor,const FGameplayEventData& Data);
	
	UFUNCTION()
	virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	virtual void OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);



};
