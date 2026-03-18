// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Game_PlayerController.generated.h"

class UUralJam_GameInstance;
class UInputAction;
class UInputMappingContext;
class UUserWidget;

UCLASS()
class URALJAM26_API AGame_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	
public:
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Look;
	
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Pause;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext_Game;
	
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext_Menu;




private:
	virtual void SetupInputComponent() override;
	virtual  void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UUralJam_GameInstance>	UralJam_GameInstance;


	// Management game mod ------------------------------------------------------------------------------------
	

	UFUNCTION()
	void SetGameMod_InMenu();
	UFUNCTION()
	void SetGameMod_InGame();
	
public:
	UFUNCTION()
	void ActivationController();

private:
	void OpenClosePauseMenu();


	// Management move ------------------------------------------------------------------------------------
	

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);

};
