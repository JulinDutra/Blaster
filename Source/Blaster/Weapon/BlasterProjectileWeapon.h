// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlasterWeapon.h"
#include "BlasterProjectileWeapon.generated.h"

class ABlasterProjectile;

UCLASS()
class BLASTER_API ABlasterProjectileWeapon : public ABlasterWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TSubclassOf<ABlasterProjectile> ProjectileClass;

public:
	virtual void Fire(const FVector& HitTarget) override;
};
