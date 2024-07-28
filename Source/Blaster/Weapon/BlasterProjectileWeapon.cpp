// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterProjectileWeapon.h"

#include "BlasterProjectile.h"
#include "Engine/SkeletalMeshSocket.h"

void ABlasterProjectileWeapon::Fire(const FVector& HitTarget)
{
	Super::Fire(HitTarget);

	if(const USkeletalMeshSocket* MuzzleFlashSocket = GetWeaponMesh()->GetSocketByName(FName("MuzzleFlash")))
	{
		const FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(GetWeaponMesh());
		const FVector Distance = HitTarget - SocketTransform.GetLocation();
		const FRotator TargetRotation = Distance.Rotation();

		if(APawn* InstigatorPawn = Cast<APawn>(GetOwner()); ProjectileClass)
		{
			FActorSpawnParameters SpawnParameters;
			SpawnParameters.Owner = GetOwner();
			SpawnParameters.Instigator = InstigatorPawn;

			if(UWorld* World = GetWorld())
			{
				World->SpawnActor<ABlasterProjectile>(ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParameters);
			}
		}
	}
}
