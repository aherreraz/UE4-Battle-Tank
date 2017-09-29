// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	ATank* GetTank();
	void Aim();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
	float AimX = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = ScreenAimingPosition)
	float AimY = 0.3333f;

private:
	UPROPERTY(EditAnywhere)
	float FireDistance = 1000000;

	bool GetSightRayHitLocation(FVector& out_HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& out_LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& out_HitLocation) const;
};
