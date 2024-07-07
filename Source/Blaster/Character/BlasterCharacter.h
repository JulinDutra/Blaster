// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Blaster/BlasterTypes/TurningInPlace.h"
#include "BlasterCharacter.generated.h"

class UBlasterCombatComponent;
class ABlasterWeapon;
class UWidgetComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UEnhancedInputComponent;
class UInputAction;
struct FInputActionValue;

UCLASS()
class BLASTER_API ABlasterCharacter : public ACharacter
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetSpringArmComponent, Category = Camera)
	TObjectPtr<USpringArmComponent> SpringArmComponent{};

	UPROPERTY(VisibleAnywhere, BlueprintGetter=GetFirstPersonCameraComponent, Category = Camera)
	TObjectPtr<UCameraComponent> FirstPersonCameraComponent;
	
	UPROPERTY(EditAnywhere, BlueprintGetter=GetDefaultMappingContext, Category = Input)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, BlueprintGetter=GetOverheadWidgetComponent, meta = (AllowPrivateAccess = "true"), Category = Widget)
	TObjectPtr<UWidgetComponent> OverheadWidget;
	
	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> EquipAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> AimAction;

	UPROPERTY(EditAnywhere, Category = Input)
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(ReplicatedUsing = OnRep_OverlappingWeapon)
	TObjectPtr<ABlasterWeapon> OverlappingWeapon;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBlasterCombatComponent> CombatComponent;

	UPROPERTY(EditAnywhere, Category = Combat)
	TObjectPtr<UAnimMontage> FireWeaponMontage;

	float AO_Yaw;

	float InterpAO_Yaw;

	float AO_Pitch;

	FRotator StartingAimRotation;

	ETurningInPlace TurningInPlace;

	UFUNCTION()
	void OnRep_OverlappingWeapon(ABlasterWeapon* LastWeapon) const;

	UFUNCTION(Server, Reliable)
	void ServerEquipButtonPressed();

	void TurnInPlace(float DeltaTime);

protected:
	virtual void BeginPlay() override;

	virtual void PossessedBy(AController* NewController) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PostInitializeComponents() override;

	virtual void Jump() override;

	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	void EquipButtonPressed();

	void CrouchButtonPressed();

	void AimButtonPressed();

	void AimButtonReleased();

	void AimOffset(float DeltaTime);

	void FireButtonPressed();

	void FireButtonReleased();

public:
	ABlasterCharacter();

	virtual void Tick(float DeltaSeconds) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION(BlueprintGetter)
	FORCEINLINE USpringArmComponent* GetSpringArmComponent() const { return SpringArmComponent; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE UInputMappingContext* GetDefaultMappingContext() const { return DefaultMappingContext; }

	UFUNCTION(BlueprintGetter)
	FORCEINLINE UWidgetComponent* GetOverheadWidgetComponent() const { return OverheadWidget; }

	FORCEINLINE float GetAO_Yaw() const { return AO_Yaw; }

	FORCEINLINE float GetAO_Pitch() const { return AO_Pitch; }

	FORCEINLINE ETurningInPlace GetTurningInPlace() const { return TurningInPlace; }

	void SetOverlappingWeapon(ABlasterWeapon* Weapon);

	bool IsWeaponEquipped();

	bool IsAiming();

	ABlasterWeapon* GetEquippedWeapon();

	void PlayFireMontage(bool bAiming);
};
