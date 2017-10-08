// Copyright 2017, Andrés Herrera, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Public/TankAimingComponent.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float AcceptanceRadius = 3000;

	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void OnTankDeath();

	virtual void SetPawn(APawn* InPawn) override;
	UTankAimingComponent* GetAimingComponent();
};
