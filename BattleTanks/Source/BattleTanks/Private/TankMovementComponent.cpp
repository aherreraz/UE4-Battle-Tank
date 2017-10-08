// Copyright 2017, Andrés Herrera, All rights reserved.

#include "TankMovementComponent.h"

void UTankMovementComponent::Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack)
{
	this->LeftTrack = LeftTrack;
	this->RightTrack = RightTrack;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!ensure(LeftTrack))
	{
		return;
	}
	if (!ensure(RightTrack))
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!ensure(LeftTrack))
	{
		return;
	}
	if (!ensure(RightTrack))
	{
		return;
	}
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForward = GetOwner()->GetActorForwardVector();
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();
	IntendMoveForward(TankForward | AIForwardIntention);
	IntendTurnRight((TankForward ^ AIForwardIntention).Z);
}
