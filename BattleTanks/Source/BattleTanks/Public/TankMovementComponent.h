// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "Public/TankTrack.h"
#include "TankMovementComponent.generated.h"

UCLASS(ClassGroup = (TankComponent), meta = (BlueprintSpawnableComponent))
class BATTLETANKS_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankTrack* LeftTrack, UTankTrack* RightTrack);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
	void IntendTurnRight(float Throw);
		
private:
	UTankTrack* LeftTrack = nullptr;
	UTankTrack* RightTrack = nullptr;
};
