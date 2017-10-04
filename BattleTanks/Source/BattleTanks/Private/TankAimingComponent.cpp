// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::Initialise(UTankBarrel* Barrel, UTankTurret* Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel && Projectile)) return;

	bool isReady = (FPlatformTime::Seconds() - LastFireTime) > ReloadTime;
	if (isReady)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel && Turret)) return;
	
	FVector LaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	if (UGameplayStatics::SuggestProjectileVelocity
		(
			this,
			LaunchVelocity,
			StartLocation,
			HitLocation,
			LaunchSpeed,
			false,
			0,
			0,
			ESuggestProjVelocityTraceOption::DoNotTrace
		))
	{
		FVector AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/// Get difference between current barrel rotation and aim direction
	float CurPitch = Barrel->GetForwardVector().Rotation().Pitch;
	float AimPitch = AimDirection.Rotation().Pitch;
	float DeltaPitch = AimPitch - CurPitch;
	
	/// Get difference between current turret rotation and aim direction
	float CurYaw = Turret->GetForwardVector().Rotation().Yaw;
	float AimYaw = AimDirection.Rotation().Yaw;
	
	// Get the best direction to rotate the turret
	float DeltaYaw = FMath::Fmod(AimYaw - CurYaw + 360.f, 360.f);
	if (DeltaYaw > 180.f)
		DeltaYaw -= 360.f;

	// Rotate the barrel and the turret
	Barrel->Elevate(DeltaPitch);
	Turret->Rotate(DeltaYaw);
}