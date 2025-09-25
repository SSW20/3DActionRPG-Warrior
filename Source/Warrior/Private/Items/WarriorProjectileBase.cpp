// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WarriorProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraComponent.h"
#include "WarriorFunctionLibrary.h"
#include "WarriorGameplayTags.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Warrior/Warrior.h"

// Sets default values
AWarriorProjectileBase::AWarriorProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	SetRootComponent(BoxComponent);

	NiagaraComponent = CreateDefaultSubobject<UNiagaraComponent>("UNiagaraComponent");
	NiagaraComponent->SetupAttachment(BoxComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");

	BoxComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxComponent->SetCollisionObjectType(ECC_Projectile);
	BoxComponent->SetCollisionResponseToChannel(ECC_Projectile, ECR_Ignore);
	BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	BoxComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	

	ProjectileMovementComponent->InitialSpeed = 500.f;
	ProjectileMovementComponent->MaxSpeed = 1000.f;
	ProjectileMovementComponent->Velocity = FVector(1.f, 0, 0);
	ProjectileMovementComponent->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 5.f;
}

void AWarriorProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentHit.AddUniqueDynamic(this, &AWarriorProjectileBase::OnProjectileHit);
	BoxComponent->OnComponentBeginOverlap.AddUniqueDynamic(this,&AWarriorProjectileBase::OnProjectileOverlap);
	if (CollisionPolicy == FProjectileCollisionPolicy::OnOverlapped)
	{
		BoxComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	}
}

void AWarriorProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileHit(Hit.ImpactPoint);
	APawn* DamagedPawn = Cast<APawn>(OtherActor);

	if (!DamagedPawn || !UWarriorFunctionLibrary::IsTargetHostile(GetInstigator(), DamagedPawn))
	{
		Destroy();
		return;
	}

	const bool bPlayerBlocking = UWarriorFunctionLibrary::NativeDoesActorHasTag(OtherActor, WarriorGameplayTags::Player_Status_Block);
	bool bValidBlock = false;
	FGameplayEventData Data;
	Data.Instigator = GetInstigator();
	Data.Target = OtherActor;
	
	if (bPlayerBlocking)
	{
		bValidBlock = UWarriorFunctionLibrary::IsBlocked(GetInstigator(),OtherActor);
	}

	if (bValidBlock)
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, WarriorGameplayTags::Player_Event_SuccessfulBlock, Data);
	}
	else
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor,WarriorGameplayTags::Shared_Event_HitReact, Data );
	}
	Destroy();
}

void AWarriorProjectileBase::OnProjectileOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	
}


