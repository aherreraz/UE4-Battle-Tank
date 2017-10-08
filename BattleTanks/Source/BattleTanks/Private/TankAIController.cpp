// Copyright 2017, Andrés Herrera, All rights reserved.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Public/Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	APawn* PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	UTankAimingComponent* AimingComponent = GetAimingComponent();

	if (!ensure(PlayerPawn))
	{
		return;
	}
	if (!ensure(AimingComponent))
	{
		return;
	}
	
	auto result = MoveToActor(PlayerPawn, AcceptanceRadius);
	AimingComponent->AimAt(PlayerPawn->GetActorLocation());
	if (AimingComponent->GetAimingStatus() == EAimingStatus::Locked)
	{
		AimingComponent->Fire();
	}
}

void ATankAIController::OnTankDeath()
{
	if (!GetPawn())
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		ATank* Tank = Cast<ATank>(InPawn);
		if (!ensure(Tank))
		{
			return;
		}
		Tank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

UTankAimingComponent* ATankAIController::GetAimingComponent()
{
	APawn* Pawn = GetPawn();
	if (!ensure(Pawn))
	{
		return nullptr;
	}
	return Pawn->FindComponentByClass<UTankAimingComponent>();
}