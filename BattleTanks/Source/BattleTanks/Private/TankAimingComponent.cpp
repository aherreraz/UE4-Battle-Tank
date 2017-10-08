// Copyright 2017, Andrés Herrera, All rights reserved.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

EAimingStatus UTankAimingComponent::GetAimingStatus() const
{
	return AimingStatus;
}

void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastFireTime = GetWorld()->GetTimeSeconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	AimingStatus = UpdatedAimingStatus();
}

void UTankAimingComponent::Initialise(UTankBarrel* Barrel, UTankTurret* Turret)
{
	this->Barrel = Barrel;
	this->Turret = Turret;
}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel))
	{
		return;
	}
	if (!ensure(Projectile))
	{
		return;
	}
	if (AimingStatus != EAimingStatus::Reloading)
	{
		AProjectile* projectile = GetWorld()->SpawnActor<AProjectile>(
			Projectile,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel))
	{
		return;
	}
	if (!ensure(Turret))
	{
		return;
	}	
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
		AimDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards();
	}	
}

void UTankAimingComponent::MoveBarrelTowards()
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
	{
		DeltaYaw -= 360.f;
	}

	// Rotate the barrel and the turret
	Barrel->Elevate(DeltaPitch);
	Turret->Rotate(DeltaYaw);
}

EAimingStatus UTankAimingComponent::UpdatedAimingStatus()
{
	if (!ensure(Barrel))
	{
		return EAimingStatus::Unknown;
	}
	if (GetWorld()->GetTimeSeconds() - LastFireTime < ReloadTime)
	{
		return EAimingStatus::Reloading;
	}
	if (Barrel->GetForwardVector().Equals(AimDirection, 0.01f))
	{
		return EAimingStatus::Locked;
	}
	else
	{
		return EAimingStatus::Aiming;
	}
}