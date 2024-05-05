// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BlasterWeapon.generated.h"

class UWidgetComponent;
class USphereComponent;
class USkeletalMeshComponent;

UENUM(BlueprintType)
enum class EBlasterWeaponState : uint8
{
	Initial,
	Equipped,
	Dropped
};

UCLASS()
class BLASTER_API ABlasterWeapon : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	TObjectPtr<USkeletalMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties", BlueprintGetter= "GetWeaponAreaSphere")
	TObjectPtr<USphereComponent> WeaponAreaSphere;

	UPROPERTY(VisibleAnywhere, Category = "Weapon Properties")
	TObjectPtr<UWidgetComponent> PickupWidget;

	UPROPERTY(ReplicatedUsing = OnRep_WeaponState, VisibleAnywhere, BlueprintSetter= "SetWeaponState")
	EBlasterWeaponState WeaponState;

	UFUNCTION()
	void OnRep_WeaponState();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:
	ABlasterWeapon();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void ShowPickupWidget(bool bShowWidget);

	UFUNCTION(BlueprintSetter)
	void SetWeaponState(EBlasterWeaponState State);

	UFUNCTION(BlueprintGetter)
	FORCEINLINE USphereComponent* GetWeaponAreaSphere() const {return WeaponAreaSphere; }
};
