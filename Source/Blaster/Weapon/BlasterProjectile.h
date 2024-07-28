// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterProjectile.generated.h"

class USoundCue;
class UProjectileMovementComponent;
class UBoxComponent;

UCLASS()
class BLASTER_API ABlasterProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> Tracer;

	TObjectPtr<UParticleSystemComponent> TracerComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UParticleSystem> ImpactParticles;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> ImpactSound;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:
	ABlasterProjectile();

	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;
};
