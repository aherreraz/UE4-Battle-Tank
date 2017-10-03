// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
	ATank* Tank = GetTank();
	if (Tank)
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController possesing: %s"), *Tank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AIController not possesing a tank"));
	}
	ATank* PlayerTank = GetPlayerTank();
	if (PlayerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank found: %s"), *PlayerTank->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player tank not found"));
	}
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetPlayerTank())
	{
		auto result = MoveToActor(GetPlayerTank(), AcceptanceRadius);
		
		if (result == EPathFollowingRequestResult::Failed)
			UE_LOG(LogTemp, Error, TEXT("result: Failed"));

		GetTank()->AimAt(GetPlayerTank()->GetActorLocation());
		GetTank()->Fire();
	}
}

ATank* ATankAIController::GetTank()
{
	return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank()
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}