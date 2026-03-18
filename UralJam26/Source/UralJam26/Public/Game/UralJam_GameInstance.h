// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UralJam_GameInstance.generated.h"

class UUserWidget;
class USettings_SaveGame;
class UProgress_SaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLevelLoading);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FGameStarted);

	UENUM(BlueprintType)
		enum class EGameState : uint8
	{
		GS_Starting,
		GS_MainMenu,
		GS_LoadingLevel,
		GS_InGame,
		GS_Paused
	};


UCLASS()
class URALJAM26_API UUralJam_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION()
	bool IsGameState_state(EGameState state)const;

	UFUNCTION()
	void SetGameState_state(EGameState state);

	UPROPERTY(VisibleAnywhere, Category = "Game | State")
	EGameState GameState;

	UFUNCTION()
	void StartContinueGame();
	
	UFUNCTION()
	void StartNewGame();
	

	virtual void Init() override;

	// Get CLASS WIDGET----------------------------------------------------------------------------------------
	
	UFUNCTION()
	TSubclassOf<UUserWidget> GetClass_Widget_PauseMenu()const;

	UFUNCTION()
	TSubclassOf<UUserWidget> GetClass_Widget_MainMenu()const;

	UFUNCTION()
	TSubclassOf<UUserWidget> GetClass_Widget_SplashScreen()const;

	UFUNCTION()
	TSubclassOf<UUserWidget> GetClass_Widget_LoadingScreen()const;



	UFUNCTION()
	bool CanContinueGame()const;
	UFUNCTION()
	bool CanNewGame()const;

	UPROPERTY(BlueprintAssignable)
	FLevelLoading OnLevelLoadedEvent;

	UPROPERTY(BlueprintAssignable)
	FGameStarted OnGameStartedEvent;

	// Settings ----------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Game |  Settings")
	void ApplySettings();
	
	// Progress ----------------------------------------------------------------------------------------
	
	UFUNCTION()
	void LoadProgress();

	UFUNCTION(BlueprintCallable)
	void SaveProgress();


	// Audio ----------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	void SetMasterVolume(float newVolume);

	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	float GetMasterVolume()const;
	
	
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Maps")
	FName Level_1_Name = TEXT("Level_1");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Maps")
	FName Level_2_Name = TEXT("Level_2");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotProgress = TEXT("Progress");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotSettings = TEXT("Settings");

	// Widget classes ----------------------------------------------------------------------------------------

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> Widget_MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> Widget_PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> Widget_SplashScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> Widget_LoadingScreen;





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
	
	UFUNCTION()
	void StartLoadAsyncLevel(FName LevelName, int32 Linkage);
};
