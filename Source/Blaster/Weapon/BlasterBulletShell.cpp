// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterBulletShell.h"

ABlasterBulletShell::ABlasterBulletShell()
{
	PrimaryActorTick.bCanEverTick = false;

	BulletShellMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BulletShellMesh"));
	SetRootComponent(BulletShellMesh);
}

void ABlasterBulletShell::BeginPlay()
{
	Super::BeginPlay();
}

