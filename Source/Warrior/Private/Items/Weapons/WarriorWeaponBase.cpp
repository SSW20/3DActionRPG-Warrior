// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/WarriorWeaponBase.h"

#include "WarriorDebugHelper.h"
#include "WarriorFunctionLibrary.h"
#include "AbilitySystem/WarriorAbilitySystemComponent.h"
#include "Components/BoxComponent.h"

// Sets default values
AWarriorWeaponBase::AWarriorWeaponBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponCollisionBox->SetupAttachment(RootComponent);
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AWarriorWeaponBase::OnComponentBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AWarriorWeaponBase::OnBoxCollisionEndOverlap);

}

void AWarriorWeaponBase::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                 const FHitResult& SweepResult)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();

	checkf(WeaponOwningPawn, TEXT("Forgot to assign an instiagtor as the owning pawn of the weapon: %s"), *GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWarriorFunctionLibrary::IsTargetHostile(WeaponOwningPawn, HitPawn))
		{
			OnWeaponHitBeginTarget.ExecuteIfBound(HitPawn);
		}
	}
}



void AWarriorWeaponBase::OnBoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APawn* WeaponOwningPawn = GetInstigator<APawn>();
	
	checkf(WeaponOwningPawn,TEXT("Forgot to assign an instiagtor as the owning pawn of the weapon: %s"),*GetName());

	if (APawn* HitPawn = Cast<APawn>(OtherActor))
	{
		if (UWarriorFunctionLibrary::IsTargetHostile(WeaponOwningPawn, HitPawn))

		{
			OnWeaponHitEndTarget.ExecuteIfBound(HitPawn);
		}
	}
}



