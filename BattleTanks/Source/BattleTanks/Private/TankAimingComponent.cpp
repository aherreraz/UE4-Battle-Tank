// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) { return; }
	
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
		UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *GetOwner()->GetName(), *AimDirection.ToString());
		MoveBarrelTowards(AimDirection);
	}	
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel* Barrel)
{
	this->Barrel = Barrel;
}
void UTankAimingComponent::SetTurretReference(UTankTurret* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/// Get difference between current barrel rotation and aim direction
	float CurPitch = Barrel->GetForwardVector().Rotation().Pitch;
	float AimPitch = AimDirection.Rotation().Pitch;
	float DeltaPitch = AimPitch - CurPitch;
	
	/// Get difference between current turret rotation and aim direction
	float CurYaw = Turret->GetForwardVector().Rotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("CurYaw: %f"), CurYaw);
	float AimYaw = AimDirection.Rotation().Yaw;
	UE_LOG(LogTemp, Warning, TEXT("AimYaw: %f"), AimYaw);
	
	// Get the best direction to rotate the turret
	float DeltaYaw = FMath::Fmod(AimYaw - CurYaw + 360.f, 360.f);
	if (DeltaYaw > 180.f)
		DeltaYaw -= 360.f;

	// Rotate the barrel and the turret
	Barrel->Elevate(DeltaPitch);
	Turret->Rotate(DeltaYaw);
}