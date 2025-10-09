// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/PickUp/WarriorPickUpBase.h"

#include "Components/SphereComponent.h"

// Sets default values
AWarriorPickUpBase::AWarriorPickUpBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereCollisionComponent");
	SphereCollisionComponent->SetSphereRadius(60.f);
	SphereCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AWarriorPickUpBase::OnSphereComponentBeginOverlap);
	SetRootComponent(SphereCollisionComponent);
}

void AWarriorPickUpBase::OnSphereComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

