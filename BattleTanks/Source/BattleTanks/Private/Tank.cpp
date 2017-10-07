// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 RoundedDamage = FMath::RoundToInt(Damage);
	CurrentHealth -= RoundedDamage;
	if (CurrentHealth <= 0)
	{
		// TODO kill tank
	}

	return 0.f;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}
