// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterWeapon.h"

#include "BlasterBulletShell.h"
#include "Blaster/Character/BlasterCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "Net/UnrealNetwork.h"

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

void ABlasterWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABlasterWeapon, WeaponState);
}

void ABlasterWeapon::OnRep_WeaponState()
{
	switch(WeaponState)
	{
		case EBlasterWeaponState::Equipped:
			ShowPickupWidget(false);
			break;
	}
}

void ABlasterWeapon::BeginPlay()
{
	Super::BeginPlay();

	if(HasAuthority())
	{
		WeaponAreaSphere->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		WeaponAreaSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
		WeaponAreaSphere->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlap);
		WeaponAreaSphere->OnComponentEndOverlap.AddDynamic(this, &ThisClass::OnSphereEndOverlap);
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
		BlasterCharacter->SetOverlappingWeapon(this);
	}
}

void ABlasterWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if(ABlasterCharacter* BlasterCharacter = Cast<ABlasterCharacter>(OtherActor); BlasterCharacter && PickupWidget)
	{
		BlasterCharacter->SetOverlappingWeapon(nullptr);
	}
}

void ABlasterWeapon::ShowPickupWidget(bool bShowWidget)
{
	if(PickupWidget)
	{
		PickupWidget->SetVisibility(bShowWidget);
	}
}

void ABlasterWeapon::SetWeaponState(EBlasterWeaponState State)
{
	WeaponState = State;

	switch(WeaponState)
	{
		case EBlasterWeaponState::Equipped:
			ShowPickupWidget(false);
			GetWeaponAreaSphere()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			break;
	}
}

void ABlasterWeapon::Fire(const FVector& HitTarget)
{
	if(FireAnimation)
	{
		WeaponMesh->PlayAnimation(FireAnimation, false);
	}

	if(BulletShellClass)
	{
		if(const USkeletalMeshSocket* AmmoEjectSocket = GetWeaponMesh()->GetSocketByName(FName("AmmoEject")))
		{
			const FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(GetWeaponMesh());

			if(UWorld* World = GetWorld())
			{
				World->SpawnActor<ABlasterBulletShell>(BulletShellClass, SocketTransform.GetLocation(), SocketTransform.GetRotation().Rotator());
			}
		}
	}
}

