// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterOverheadWidget.h"

#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UBlasterOverheadWidget::SetDisplayRoleText(const FString& TextToDisplay) const
{
	if(DisplayRoleText)
	{
		DisplayRoleText->SetText(FText::FromString(TextToDisplay));
	}
}

void UBlasterOverheadWidget::ShowPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;

	switch (RemoteRole)
	{
		case ROLE_Authority:
			Role = FString("Authority");
			break;

		case ROLE_AutonomousProxy:
			Role = FString("Autonomous Proxy");
			break;

		case ROLE_SimulatedProxy:
			Role = FString("Simulated Proxy");
			break;

		case ROLE_None:
			Role = FString("None");
			break;

		default:
			break;
	}

	FString RemoteRoleString = FString::Printf(TEXT("Remote Role: %s"), *Role);
	SetDisplayRoleText(RemoteRoleString);
}

void UBlasterOverheadWidget::ShowPlayerName(APlayerState* InPlayerState)
{
	if(DisplayNameText && IsValid(InPlayerState))
	{
		DisplayNameText->SetText(FText::FromString(InPlayerState->GetPlayerName()));
	}
}

void UBlasterOverheadWidget::NativeDestruct()
{
	RemoveFromParent();

	Super::NativeDestruct();
}
