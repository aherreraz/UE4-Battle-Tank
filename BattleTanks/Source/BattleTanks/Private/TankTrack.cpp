// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
	UE_LOG(LogTemp, Warning, TEXT("%s throttle = %f"), *GetName(), Throttle);
	FVector ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = GetOwner()->GetRootPrimitiveComponent();
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}