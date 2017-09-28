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

ATank* ATankPlayerController::GetTank()
{
	return Cast<ATank>(GetPawn());
}