// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets\UW_MainMenu.h"

void UUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartNewGameButton)
	{
		StartNewGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnStartNewGameButtonClicked);
	}
	if (ContinueGameButton)
	{
		ContinueGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnContinueGameButtonClicked);
	}
	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnExitGameButtonClicked);
	}
	if (SoundVolumeSlider)
	{
		SoundVolumeSlider->OnValueChanged.AddDynamic(this,&UUW_MainMenu::OnMasterVolumeChanged);
	}
	
	UralJam_GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	if (UralJam_GameInstance)
	{
		SoundVolumeSlider->SetValue(UralJam_GameInstance->GetMasterVolume());
		if (!UralJam_GameInstance->CanContinueGame())
		{
			if (ContinueGameButton)
			{
				ContinueGameButton->SetIsEnabled(false);
			}
		}
	}
}



void UUW_MainMenu::OnStartNewGameButtonClicked()
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


void UUW_MainMenu::OnContinueGameButtonClicked()
{
	if (UralJam_GameInstance)
	{
	// Логика продолжения игры	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu::OnContinueGameButtonClicked: UralJam_GameInstance not found!"));
	}

}

void UUW_MainMenu::OnExitGameButtonClicked()
{

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("quit");
	}
}

void UUW_MainMenu::OnMasterVolumeChanged(float Value)
{
	if (UralJam_GameInstance )
	{
		UralJam_GameInstance->SetMasterVolume(SoundVolumeSlider->GetValue());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu: UralJam_GameInstance not found!"));
	}
}

