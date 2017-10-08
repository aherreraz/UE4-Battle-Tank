// Copyright 2017, Andrés Herrera, All rights reserved.

#include "TankTrack.h"
#include "Engine/World.h"

UTankTrack::UTankTrack()
{
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	AddSideForce();
	CurrentThrottle = 0.f;
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	GetTankRoot()->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::AddSideForce()
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float SideSpeed = GetComponentVelocity() | GetRightVector();
	FVector CounterAcceleration = -SideSpeed * GetRightVector() / DeltaTime;
	FVector CounterForce = (GetTankRoot()->GetMass() * CounterAcceleration) / 2;
	GetTankRoot()->AddForce(CounterForce);
}

UPrimitiveComponent* UTankTrack::GetTankRoot()
{
	if (TankRoot)
	{
		return TankRoot;
	}
	return TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}