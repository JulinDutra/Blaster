// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BlasterOverheadWidget.generated.h"

class UTextBlock;

UCLASS()
class BLASTER_API UBlasterOverheadWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DisplayRoleText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> DisplayNameText;

	void SetDisplayRoleText(const FString& TextToDisplay) const;

	UFUNCTION(BlueprintCallable)
	void ShowPlayerNetRole(APawn* InPawn);

	UFUNCTION(BlueprintCallable)
	void ShowPlayerName(APlayerState* InPlayerState);

protected:
	virtual void NativeDestruct() override;
};
