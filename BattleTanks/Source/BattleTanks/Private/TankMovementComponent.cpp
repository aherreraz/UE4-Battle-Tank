// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	UE_LOG(LogTemp, Warning, TEXT("Moving forward: %f"), Throw);
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}