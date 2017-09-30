// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
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
void UTankAimingComponent::SetTurretReference(UStaticMeshComponent* Turret)
{
	this->Turret = Turret;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	/// Get difference between current barrel rotation and aim direction
	FRotator BarrelRotator = Barrel->GetForwardVector().Rotation();
	FRotator AimRotator = AimDirection.Rotation();
	FRotator DeltaRotator = AimRotator - BarrelRotator;
	
	Barrel->Elevate(DeltaRotator.Pitch);
}