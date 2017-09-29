// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "Public/Tank.h"
#include "AIController.h"
#include "TankAIController.generated.h"

UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetTank();
	ATank* GetPlayerTank();
};
