// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_DialogFrame.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FReceivedAnswer, bool, Answer);

class UButton;
/**
 * 
 */
UCLASS()
class URALJAM26_API UUW_DialogFrame : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

	// Cancel button  --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;
	UFUNCTION()
	void OnCancelButtonClicked();

	// Okay button  --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* OkayButton;
	UFUNCTION()
	void OnOkayButtonClicked();
public:
	FReceivedAnswer OnReceivedAnswerEvent;
};
