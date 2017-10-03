// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Public/Tank.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void Tick(float DeltaTime) override;
	
	void Aim();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	ATank* GetTank() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ScreenAimingPosition)
	float AimX = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = ScreenAimingPosition)
	float AimY = 0.3333f;

private:
	UPROPERTY(EditDefaultsOnly)
	float FireDistance = 1000000;

	bool GetSightRayHitLocation(FVector& out_HitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector& out_LookDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector& out_HitLocation) const;
};
