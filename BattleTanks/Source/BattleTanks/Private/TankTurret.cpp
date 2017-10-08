// Copyright 2017, Andr�s Herrera, All rights reserved.

#include "TankTurret.h"
#include "Engine/World.h"

void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, 1);
	float RotationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float Rotation = RotationChange + RelativeRotation.Yaw;
	SetRelativeRotation(FRotator(0.f, Rotation, 0.f));
}