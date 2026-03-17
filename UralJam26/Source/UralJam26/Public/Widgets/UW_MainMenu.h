// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Game\UralJam_GameInstance.h"
#include "Components\Button.h"
#include "Components\Slider.h"
#include "UW_MainMenu.generated.h"

class UGame_for_UralJam_GameInstance;
class AMenu_PlayerController;

UCLASS(Abstract)
class URALJAM26_API UUW_MainMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;
	
private:
	// NewGameButton --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* StartNewGameButton;
	UFUNCTION()
	void OnStartNewGameButtonClicked();
	
	// ContinueGameButton --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* ContinueGameButton;
	UFUNCTION()
	void OnContinueGameButtonClicked();


	//ExitGameButton --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;
	UFUNCTION()
	void OnExitGameButtonClicked();

	UPROPERTY(meta=(BindWidget))
	USlider* SoundVolumeSlider;

	UFUNCTION()
	void OnMasterVolumeChanged(float Value);

	UPROPERTY()
	TObjectPtr<UUralJam_GameInstance> UralJam_GameInstance;
};
