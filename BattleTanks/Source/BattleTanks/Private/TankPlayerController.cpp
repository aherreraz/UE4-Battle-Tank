// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UTankAimingComponent* AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent)) return;

	FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Aim();
}

void ATankPlayerController::Aim()
{
	UTankAimingComponent* AimingComponent = GetAimingComponent();
	if (!ensure(AimingComponent)) return;
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
		AimingComponent->AimAt(HitLocation);
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation) const
{
	/// Find the crosshair position in pixel coordinates
	int32 ScreenWidth, ScreenHeight;
	GetViewportSize(ScreenWidth, ScreenHeight);
	FVector2D ScreenPosition = FVector2D(ScreenWidth * AimX, ScreenHeight * AimY);

	/// Deproject the screen position of the crosshair to a world direction
	FVector LookDirection;
	if (GetLookDirection(ScreenPosition, LookDirection))
		return GetLookVectorHitLocation(LookDirection, out_HitLocation);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenPosition, FVector& out_LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(ScreenPosition.X, ScreenPosition.Y, CameraWorldLocation, out_LookDirection);
}
bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& out_HitLocation) const
{
	FHitResult HitResult;
	FVector StartLocation = PlayerCameraManager->GetCameraLocation();
	FVector EndLocation = StartLocation + LookDirection * LineTraceDistance;
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		out_HitLocation = HitResult.Location;
		return true;
	}
	out_HitLocation = FVector(0.f);
	return false;
}

UTankAimingComponent* ATankPlayerController::GetAimingComponent()
{
	APawn* Pawn = GetPawn();
	if (!ensure(Pawn)) return nullptr;
	return Pawn->FindComponentByClass<UTankAimingComponent>();
}