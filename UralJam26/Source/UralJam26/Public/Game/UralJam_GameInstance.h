// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SavesObjects\Progress_SaveGame.h"
#include "SavesObjects\Settings_SaveGame.h"
#include "Sound/SoundClass.h"
#include "UralJam_GameInstance.generated.h"

UCLASS()
class URALJAM26_API UUralJam_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	
	
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	virtual void Init() override;
	// access functions----------------------------------------------------------------------------------------
	UFUNCTION()
	TSubclassOf<UUserWidget> GetClass_Widget_PauseMenu()const;
	UFUNCTION()
	TSubclassOf<UUserWidget> GetClass_Widget_MainMenu()const;
	UFUNCTION()
	bool CanContinueGame()const;



	// Settings----------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Game |  Settings")
	void ApplySettings();
	
	// Progress----------------------------------------------------------------------------------------
	
	UFUNCTION()
	void LoadProgress();


	// Audio----------------------------------------------------------------------------------------
	
	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	void SetMasterVolume(float newVolume);

	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	float GetMasterVolume()const;
	
	
	
protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
	FName LevelName = TEXT("MainLevel");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotProgress = TEXT("Progress");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotSettings = TEXT("Settings");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	TSubclassOf<UUserWidget> Widget_MainMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	TSubclassOf<UUserWidget> Widget_PauseMenu;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	TObjectPtr<USoundClass> MasterSoundClass;

private:

	// Save fails----------------------------------------------------------------------------------------

	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<USettings_SaveGame> Settings;

	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<UProgress_SaveGame> Progress;
};
