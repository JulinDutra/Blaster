// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterProjectile.generated.h"

class UBoxComponent;

UCLASS()
class BLASTER_API ABlasterProjectile : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> CollisionBox;

protected:
	virtual void BeginPlay() override;

public:
	ABlasterProjectile();

	virtual void Tick(float DeltaTime) override;
};
