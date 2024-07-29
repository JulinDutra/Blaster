// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterBulletShell.generated.h"

class USoundCue;

UCLASS()
class BLASTER_API ABlasterBulletShell : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> BulletShellMesh;

	UPROPERTY(EditAnywhere)
	float ShellEjectionImpulse = 10.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundCue> ShellSound;

public:
	ABlasterBulletShell();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
