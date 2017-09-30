// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankPlayerController.h"
#include "Engine/World.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController possesing: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController not possesing a tank"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Aim();
}

ATank* ATankPlayerController::GetTank()
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::Aim()
{
	if (!GetTank()) { return; }
	
	FVector HitLocation;
	if (GetSightRayHitLocation(HitLocation))
	{
		GetTank()->AimAt(HitLocation);
	}
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
		GetLookVectorHitLocation(LookDirection, out_HitLocation);
	return true;
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
	FVector EndLocation = StartLocation + LookDirection * FireDistance;
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