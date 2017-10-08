// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"


ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	// Apply Damage
	int32 ActualDamage = FMath::Clamp(FMath::RoundToInt(Damage), 0, CurrentHealth);
	CurrentHealth -= ActualDamage;

	// Update Health Percent
	float HeatlhPercent = 1.f * CurrentHealth / StartingHealth;
	UpdateHealthPercent(HeatlhPercent);

	// Kill tank
	if (CurrentHealth <= 0)
		OnDeath.Broadcast();

	return 0.f;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}
