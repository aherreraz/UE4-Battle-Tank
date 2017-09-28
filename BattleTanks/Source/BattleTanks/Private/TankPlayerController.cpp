// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/TankPlayerController.h"

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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& out_HitLocation)
{
	out_HitLocation = FVector(1.f);
	return true;
}