// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlasterCombatComponent.generated.h"


class ABlasterCharacter;
class ABlasterWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BLASTER_API UBlasterCombatComponent : public UActorComponent
{
	GENERATED_BODY()

	friend class ABlasterCharacter;

	UPROPERTY(ReplicatedUsing = OnRep_EquippedWeapon)
	TObjectPtr<ABlasterWeapon> EquippedWeapon;

	TObjectPtr<ABlasterCharacter> Character;

	UPROPERTY(Replicated)
	bool bAiming;

protected:
	virtual void BeginPlay() override;

	void SetAiming(bool bIsAiming);

	UFUNCTION(Server, Reliable)
	void ServerSetAiming(bool bIsAiming);

	UFUNCTION()
	void OnRep_EquippedWeapon() const;

public:
	UBlasterCombatComponent();

	void EquipWeapon(ABlasterWeapon* InEquippedWeapon);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
};
