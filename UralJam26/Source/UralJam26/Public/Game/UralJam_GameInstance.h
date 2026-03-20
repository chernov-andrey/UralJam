// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UralJam_GameInstance.generated.h"

class UUserWidget;
class USettings_SaveGame;
class UProgress_SaveGame;
class AGame_PlayerController;
class UUW_Cutscene;
class UUW_SplashScreen;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelLoading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStarted);//игра начинается либо новая либо продолжение, открывается карта

	UENUM(BlueprintType)
		enum class EGameState : uint8
	{
		GS_Starting,
		GS_MainMenu,
		GS_Loading,
		GS_InGame,
		GS_Paused,
		GS_Cutscene
	};


UCLASS()
class URALJAM26_API UUralJam_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	TMap<EGameState, bool> MapState;
	void InitMapState();


	void SetPlayerController(TObjectPtr<AGame_PlayerController> lPlayerController);
private:
	UPROPERTY()
	TObjectPtr<AGame_PlayerController> PlayerController;



	// Splash Screen ------------------------------------------------------------------------------------------

public:

	
	UFUNCTION()
	void CreateSplashScreen_Widget();
	UFUNCTION()
	void RemoveSplashScreen_Widget();
private:
	UPROPERTY()
	TObjectPtr<UUW_SplashScreen> SplashScreen_Widget;


	// Loading Screen ------------------------------------------------------------------------------------------

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings Controller Game_PlayerController | Settings view widgets",
		meta = (ClampMin = "1.0", ClampMax = "15.0",
			UIMin = "1.0", UIMax = "15.0"))
	float MinLifeTime_LoadingScreen = 2.0f; 

	UFUNCTION()
	void CreateLoadingScreen_Widget();
	UFUNCTION()
	void RemoveLoadingScreen_Widget();
private:
	
	UPROPERTY()
	TObjectPtr<UUserWidget> LoadingScreen_Widget;


	// Pause Menu ------------------------------------------------------------------------------------------


public:
	UFUNCTION()
	void OpenClosePauseMenu();
private:
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenu;

	UFUNCTION()
	void HiddenPauseMenu();
	UFUNCTION()
	void ShowPauseMenu();

	// Main Menu ------------------------------------------------------------------------------------------

public:
	UFUNCTION()
	void CreateMainMenu_Widget();
	UFUNCTION()
	void RemoveMainMenu_Widget();
private:
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenu_Widget;



public:


	UFUNCTION()
	bool IsGameState_state(EGameState state)const;

	UFUNCTION()
	void SetGameState_state(EGameState state, bool val);

	UPROPERTY(VisibleAnywhere, Category = "Game | State")
	EGameState GameState;

	
	
	UFUNCTION()//процесс запуска НОВОЙ игровой сессии 
	void StartNewSession();
	
	UFUNCTION()// Создаем виджет катсцены 
	void LaunchCutscene(TSubclassOf<UUW_Cutscene> ClassCutsceneWidget);
	UFUNCTION()
	void EndLaunchCutscene(UUW_Cutscene* CutscenePtr);
private:
	UPROPERTY()
	TObjectPtr<UUW_Cutscene> Cutscene_Widget;

public:

	UFUNCTION() // Запуск Физики активация контроллера
	void StartPlay();

	virtual void Init() override;





	UPROPERTY(BlueprintAssignable)
	FLevelLoading OnLevelLoadedEvent;

	UPROPERTY(BlueprintAssignable)
	FGameStarted OnFirstLevelLoadedEvent;

	// Settings ----------------------------------------------------------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Game |  Settings")
	void ApplySettings();
	
	// Progress ----------------------------------------------------------------------------------------

	

	// Audio ----------------------------------------------------------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	void SetMasterVolume(float newVolume);

	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	float GetMasterVolume()const;

	
protected:
	//Names ----------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Maps")
	FName Level_1_Name = TEXT("Level_1");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Maps")
	FName Level_2_Name = TEXT("Level_2");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotProgress = TEXT("Progress");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotSettings = TEXT("Settings");

	UPROPERTY(EditAnywhere, Category = "Game |  Maps")
	FName TargetPoint_Tag_1;

	// Widget classes ----------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> WidgetType_MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> WidgetType_PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUW_SplashScreen> WidgetType_SplashScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> WidgetType_LoadingScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUW_Cutscene> WidgetType_1_Cutscene;



	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	TObjectPtr<USoundClass> MasterSoundClass;

private:

	// Save fails ----------------------------------------------------------------------------------------

	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<USettings_SaveGame> Settings;

	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<UProgress_SaveGame> Progress;

	//Load level ----------------------------------------------------------------------------------------
	UFUNCTION()
	void LoadedLevel(int32 Linkage);
public:
	UFUNCTION()
	void ReloadFirstLevel(int32 i);
private:
		UFUNCTION()
	void StartLoadAsyncLevel(FName LevelName, int32 Linkage);
	UPROPERTY(VisibleAnywhere)
	ULevelStreaming* Current_StreamingLevel;
};
