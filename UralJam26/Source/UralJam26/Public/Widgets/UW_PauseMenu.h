// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_PauseMenu.generated.h"

class AMenu_PlayerController;
class AGame_PlayerController;
class UButton;
class USlider;
class UUralJam_GameInstance;
class UUW_DialogFrame;

UCLASS()
class URALJAM26_API UUW_PauseMenu : public UUserWidget
{
	GENERATED_BODY()
protected:
	virtual void NativeConstruct() override;

private:
	// NewGameButton  --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* StartNewGameButton;

	UFUNCTION()
	void OnStartNewGameButtonClicked();



public:
	UFUNCTION(BlueprintImplementableEvent)
	void ShowDialog();

	UFUNCTION(BlueprintImplementableEvent)
	void HiddenDialog();
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Pre_ClosePauseMenu();

	
	UFUNCTION(BlueprintCallable)
	void ClosePauseMenu();
	

	
	//ExitGameButton --------------------------------------------------------------------------
	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;
	UFUNCTION()
	void OnExitGameButtonClicked();

	UPROPERTY(meta = (BindWidget))
	USlider* SoundVolumeSlider;
	
	UPROPERTY(meta = (BindWidget))
	UUW_DialogFrame* DialogFrame;

	UFUNCTION()
	void OnMasterVolumeChanged(float Value);
	
	UFUNCTION()
	void ReceivedAnswer_NewGame(bool Answer);

		UPROPERTY()
	TObjectPtr<UUralJam_GameInstance> UralJam_GameInstance;
};
