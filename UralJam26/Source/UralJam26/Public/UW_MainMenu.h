// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UralJam_GameInstance.h"
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
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	UPROPERTY(meta=(BindWidget))
	USlider* SoundVolumeSlider;

	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnExitGameButtonClicked();

	UFUNCTION()
	void OnMasterVolumeChanged(float Value);

	
	UPROPERTY()
	TObjectPtr<UUralJam_GameInstance> UralJam_GameInstance;
};
