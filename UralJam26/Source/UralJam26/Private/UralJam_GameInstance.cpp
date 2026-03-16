// Fill out your copyright notice in the Description page of Project Settings.


#include "UralJam_GameInstance.h"

void UUralJam_GameInstance::Init()
{
	Super::Init();
	LoadSettings();
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
	Settings = Cast< USettings_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, 0));
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
	if (SaveSlotName.IsEmpty()) 
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: SaveSlotName is Empty!"));
		return;
	}
	if (Settings.IsNull())
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: Settings is null!222"));
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::SaveSettings: TRY SAVEGAME!"));
	UGameplayStatics::SaveGameToSlot(Settings, SaveSlotName, 0);

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