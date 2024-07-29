// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterBulletShell.generated.h"

UCLASS()
class BLASTER_API ABlasterBulletShell : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BulletShellMesh;

public:
	ABlasterBulletShell();

protected:
	virtual void BeginPlay() override;
};
