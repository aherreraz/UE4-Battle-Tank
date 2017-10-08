// Copyright 2017, Andrés Herrera, All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();
	void LaunchProjectile(float Speed);

protected:
	virtual void BeginPlay() override;
	

private:
	UPROPERTY(VisibleAnywhere, Category = Components)
	UStaticMeshComponent* CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* LaunchBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	UParticleSystemComponent* ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = Components)
	URadialForceComponent* ExplosionForce = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float ProjectileDamage = 20.f;

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	float DestroyDelay = 5.f;

	UProjectileMovementComponent* ProjectileMovementComponent = nullptr;
	

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);

	void OnTimerExpire();
};
