// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Settings_SaveGame.h"
#include "Sound/SoundClass.h"
#include "UralJam_GameInstance.generated.h"

class USettings_SaveGame;
 
UCLASS()
class URALJAM26_API UUralJam_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	virtual void Init() override;


	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Game |  Settings")
	void ApplySettings();

	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	void SetMasterVolume(float newVolume);

	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	float GetMasterVolume()const;

	UPROPERTY(EditAnywhere, Category = "Game")
	FName LevelName = TEXT("MainLevel");

	UPROPERTY(EditAnywhere, Category = "Game | Save/Load")
	FString SaveSlotName = TEXT("Settings");
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<USettings_SaveGame> Settings;

	UPROPERTY(EditAnywhere, Category = "Game | Settings")
	TObjectPtr<USoundClass> MasterSoundClass;

};
