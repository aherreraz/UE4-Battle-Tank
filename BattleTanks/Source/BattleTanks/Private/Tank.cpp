// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Engine/World.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	aiming = FindComponentByClass<UTankAimingComponent>();
}

void ATank::AimAt(FVector HitLocation)
{
	aiming->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	bool isReady = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (Barrel && isReady)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}