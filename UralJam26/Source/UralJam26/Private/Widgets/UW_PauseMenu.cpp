// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets\UW_PauseMenu.h"

void UUW_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartNewGameButton)
	{
		StartNewGameButton->OnClicked.AddDynamic(this, &UUW_PauseMenu::OnStartNewGameButtonClicked);
	}
	if (ClouseMenuButton)
	{
		ClouseMenuButton->OnClicked.AddDynamic(this, &UUW_PauseMenu::OnClouseMenuButtonClicked);
	}
	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UUW_PauseMenu::OnExitGameButtonClicked);
	}
	if (SoundVolumeSlider)
	{
		SoundVolumeSlider->OnValueChanged.AddDynamic(this, &UUW_PauseMenu::OnMasterVolumeChanged);
	}

	UralJam_GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	if (UralJam_GameInstance)
	{
		SoundVolumeSlider->SetValue(UralJam_GameInstance->GetMasterVolume());
	}
}
void UUW_PauseMenu::OnStartNewGameButtonClicked()
{
	if (UralJam_GameInstance)
	{
		UralJam_GameInstance->StartGame();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu: UralJam_GameInstance not found!"));
	}
}
void UUW_PauseMenu::OnClouseMenuButtonClicked()
{
	if (AGame_PlayerController* PlayerController = Cast<AGame_PlayerController>(GetOwningPlayer()))
	{
		PlayerController->OpenCloseMenu();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("UUW_PauseMenu::OnClouseMenuButtonClicked:  PlayerController FAIL CAST to AGame_PlayerController!"));
	}
}
void UUW_PauseMenu::OnExitGameButtonClicked()
{

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("quit");
	}
}

void UUW_PauseMenu::OnMasterVolumeChanged(float Value)
{
	if (UralJam_GameInstance)
	{
		UralJam_GameInstance->SetMasterVolume(SoundVolumeSlider->GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu: UralJam_GameInstance not found!"));
	}
}
