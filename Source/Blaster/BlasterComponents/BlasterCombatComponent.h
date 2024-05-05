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

	TObjectPtr<ABlasterWeapon> EquippedWeapon;

	TObjectPtr<ABlasterCharacter> Character;

public:
	UBlasterCombatComponent();

	void EquipWeapon(ABlasterWeapon* InEquippedWeapon);

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
