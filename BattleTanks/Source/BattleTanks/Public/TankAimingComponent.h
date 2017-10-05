// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/ActorComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/Projectile.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimingStatus : uint8
{
	Unknown,
	Reloading,
	Aiming,
	Locked
};

UCLASS( ClassGroup=(TankComponent), meta=(BlueprintSpawnableComponent) )
class BATTLETANKS_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Aiming)
	EAimingStatus GetAimingStatus() const;

protected:
	virtual void BeginPlay() override;

public:
	EAimingStatus AimingStatus = EAimingStatus::Reloading;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Initialise(UTankBarrel* Barrel, UTankTurret* Turret);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	void AimAt(FVector HitLocation);
	
private:
	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	TSubclassOf<AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTime = 3.f;

	float LastFireTime = 0.f;
	UTankBarrel* Barrel = nullptr;
	UTankTurret* Turret = nullptr;
	FVector AimDirection;

	void MoveBarrelTowards();
	EAimingStatus UpdatedAimingStatus();
};
