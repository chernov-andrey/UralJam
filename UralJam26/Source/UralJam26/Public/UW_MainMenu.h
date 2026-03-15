// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UralJam_GameInstance.h"
#include "Components\Button.h"
#include "UW_MainMenu.generated.h"

class UButton;
class UGame_for_UralJam_GameInstance;
class AMenu_PlayerController;
UCLASS()
class URALJAM26_API UUW_MainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* ExitGameButton;

	UFUNCTION()
	void OnStartGameButtonClicked();

	UFUNCTION()
	void OnExitGameButtonClicked();
private:
	UUralJam_GameInstance* GetUralJam_GameInstance();
	virtual void NativeConstruct() override;
};
