// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets\UW_PauseMenu.h"
#include "Game\UralJam_GameInstance.h"
#include "Components\Button.h"
#include "Components\Slider.h"
#include "Game\Game_PlayerController.h"

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
		UralJam_GameInstance->StartNewGame();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu::OnStartNewGameButtonClicked: UralJam_GameInstance not found!"));
	}
}
void UUW_PauseMenu::OnClouseMenuButtonClicked()
{
	if (UralJam_GameInstance)
	{
		UralJam_GameInstance->OpenClosePauseMenu();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu::OnClouseMenuButtonClicked: UralJam_GameInstance not found!"));
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
