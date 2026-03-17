// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\UralJam_GameInstance.h"

void UUralJam_GameInstance::Init()
{
	Super::Init();
	LoadSettings();
	LoadProgress();
}
void  UUralJam_GameInstance::StartGame()
{
	UE_LOG(LogTemp, Error, TEXT("GameInstance->StartGame"));//UralGame_LogEvents

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, LevelName);
	}
}

void UUralJam_GameInstance::LoadSettings()
{
	Settings = Cast< USettings_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotSettings, 0));
	if (Settings)
	{
		
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadSettings  is success!"));
	}
	else
	{
		Settings = Cast< USettings_SaveGame>(UGameplayStatics::CreateSaveGameObject(USettings_SaveGame::StaticClass()));
		Settings->MasterVolume = 0.5f;
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadSettings  is fails!"));
	}
	ApplySettings();
}

void UUralJam_GameInstance::SaveSettings()
{
	if (!Settings)
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: Settings is null!"));
		return;
	}
	if (SaveSlotSettings.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: SaveSlotName is Empty!"));
		return;
	}
	/*	if (Settings.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: Settings is null!222"));
		return;
	}
	*/
	UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: TRY SAVEGAME!"));
	UGameplayStatics::SaveGameToSlot(Settings, SaveSlotSettings, 0);

}
void UUralJam_GameInstance::ApplySettings()
{
	if (MasterSoundClass&&Settings)
	{		
		MasterSoundClass->Properties.Volume = Settings->MasterVolume;				
	}
	SaveSettings();
}

void UUralJam_GameInstance::SetMasterVolume(float newVolume)
{
	check(Settings&&"UUralJam_GameInstance::SetMasterVolume FALE!")
		Settings->MasterVolume = FMath::Clamp(newVolume, 0.001f, 1.0f);
		ApplySettings();
}

float UUralJam_GameInstance::GetMasterVolume()const
{
	check(Settings && "UUralJam_GameInstance::GetMasterVolume FALE!")
		return Settings->MasterVolume;
}

void UUralJam_GameInstance::LoadProgress()
{
	Progress = Cast< UProgress_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotProgress, 0));
	if (Progress)
	{
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadProgress: success load Progress!"));
	}
	else
	{
		Progress = Cast< UProgress_SaveGame>(UGameplayStatics::CreateSaveGameObject(UProgress_SaveGame::StaticClass()));
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadProgress: fail load Progress! "));
	}
}
TSubclassOf<UUserWidget> UUralJam_GameInstance::GetClass_Widget_PauseMenu() const
{
	return Widget_PauseMenu;
}
TSubclassOf<UUserWidget> UUralJam_GameInstance::GetClass_Widget_MainMenu()const
{
	return Widget_MainMenu;
}

bool UUralJam_GameInstance::CanContinueGame() const
{
	if (Progress)
	{
		return !(Progress->bIsNewGame);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::anContinueGame: not found save progress! "));
		return false;
	}
}

