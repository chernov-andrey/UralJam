// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Game\UralJam_GameInstance.h"
#include "GameFramework/PlayerController.h"
#include "Game_PlayerController.generated.h"


UCLASS()
class URALJAM26_API AGame_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	UFUNCTION()
	void OpenCloseMenu();
public:
	UPROPERTY(EditAnywhere, Category = "Input Settings")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditAnywhere, Category = "Input Settings")
	TObjectPtr<UInputAction> IA_Look;
	
	UPROPERTY(EditAnywhere, Category = "Input Settings")
	TObjectPtr<UInputAction> IA_Pause;

	UPROPERTY(EditAnywhere, Category = "Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext;
private:
	virtual  void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenu;
	
	UFUNCTION()
	bool HiddenMainMenu();
	UFUNCTION()
	bool ShowMainMenu();
	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);

	virtual void SetupInputComponent() override;
};
