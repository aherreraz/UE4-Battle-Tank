// Copyright 2017, Andrés Herrera, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

UCLASS(ClassGroup = (TankComponent), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	void Elevate(float RelativeSpeed);

private:
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxDegreesPerSecond = 10.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MinElevationDegrees = 0.f;
	
	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float MaxElevationDegrees = 50.f;
};
