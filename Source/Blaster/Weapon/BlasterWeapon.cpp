// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterWeapon.h"

#include "Blaster/Character/BlasterCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
ABlasterWeapon::ABlasterWeapon()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	WeaponMesh->SetupAttachment(RootComponent);
	SetRootComponent(WeaponMesh);

	WeaponMesh->SetCollisionResponseToAllChannels(ECR_Block);
	WeaponMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	WeaponAreaSphere = CreateDefaultSubobject<USphereComponent>(TEXT("AreaSphere"));
	WeaponAreaSphere->SetupAttachment(RootComponent);

	WeaponAreaSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	WeaponAreaSphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	PickupWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("PickupWidget"));
	PickupWidget->SetupAttachment(RootComponent);
}

void ABlasterWeapon::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		WeaponAreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponAreaSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		WeaponAreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
	}

	if(PickupWidget)
	{
		PickupWidget->SetVisibility(false);
	}
}

void ABlasterWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor); BlasterCharacter && PickupWidget)
	{
		PickupWidget->SetVisibility(true);
	}
}

void ABlasterWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

