// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	float SideSpeed = GetComponentVelocity() | GetRightVector();
	FVector CounterAcceleration = -SideSpeed * GetRightVector() / DeltaTime;
	FVector CounterForce = (GetTankRoot()->GetMass() * CounterAcceleration) / 2;
	UE_LOG(LogTemp, Warning, TEXT("Mass: %f"), GetTankRoot()->GetMass());
	GetTankRoot()->AddForce(CounterForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	GetTankRoot()->AddForceAtLocation(ForceApplied, ForceLocation);
}

UPrimitiveComponent* UTankTrack::GetTankRoot()
{
	if (TankRoot)
		return TankRoot;
	return TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
}