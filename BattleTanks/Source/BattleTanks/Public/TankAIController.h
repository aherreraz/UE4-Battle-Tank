// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Public/Tank.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
public:
	virtual void Tick(float DeltaTime) override;

	ATank* GetTank();
	ATank* GetPlayerTank();

	float AcceptanceRadius = 3000;
};
