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
	TObjectPtr<UInputMappingContext> MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings Controller Game_PlayerController | Settings view widgets", 
		meta = (ClampMin = "1.0", ClampMax = "15.0",
			UIMin = "1.0", UIMax = "15.0"))
	float LifeTime_SplashScreen = 2.0f; //Время существования splash screen widget


private:
	virtual void SetupInputComponent() override;
	virtual  void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UUralJam_GameInstance>	UralJam_GameInstance;


	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenu_Widget;

	// Splash Screen Widget ------------------------------------------------------------------------------------

	UPROPERTY()
	TObjectPtr<UUserWidget> SplashScreen_Widget;
	
	UFUNCTION()
	void CreateSplashScreen_Widget();
	UFUNCTION()
	void RemoveSplashScreen_Widget();
	FTimerHandle TimerHandle_LifeTemporaryWidget;
	

	// Management game mod ------------------------------------------------------------------------------------
	

	UFUNCTION()
	void SetGameMod_InMenu();
	UFUNCTION()
	void SetGameMod_InGame();

	

	// Pause ------------------------------------------------------------------------------------
public:
	UFUNCTION()
	void OpenClosePauseMenu();
private:
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenu;

	UFUNCTION()
	bool HiddenPauseMenu();
	UFUNCTION()
	bool ShowPauseMenu();
	

	// Management move ------------------------------------------------------------------------------------
	

	UFUNCTION()
	void Move(const FInputActionValue& Value);
	UFUNCTION()
	void Look(const FInputActionValue& Value);

};
