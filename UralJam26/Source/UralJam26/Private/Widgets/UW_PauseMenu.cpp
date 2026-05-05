// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets\UW_PauseMenu.h"
#include "Game\UralJam_GameInstance.h"
#include "Components\Button.h"
#include "Components\Slider.h"
#include "Widgets\UW_DialogFrame.h"
#include "Game\Game_PlayerController.h"

void UUW_PauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	check(StartNewGameButton);
	StartNewGameButton->OnClicked.AddDynamic(this, &UUW_PauseMenu::OnStartNewGameButtonClicked);
		
	check(ExitGameButton);
	ExitGameButton->OnClicked.AddDynamic(this, &UUW_PauseMenu::OnExitGameButtonClicked);
	
	check(SoundVolumeSlider);
	SoundVolumeSlider->OnValueChanged.AddDynamic(this, &UUW_PauseMenu::OnMasterVolumeChanged);
	
	UralJam_GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	if (UralJam_GameInstance)
	{
		SoundVolumeSlider->SetValue(UralJam_GameInstance->GetMasterVolume());
	}
}
void UUW_PauseMenu::OnStartNewGameButtonClicked()
{
	check(DialogFrame);
	DialogFrame->OnReceivedAnswerEvent.AddDynamic(this, &ThisClass::ReceivedAnswer_NewGame);
	ShowDialog();
}


void UUW_PauseMenu::Pre_ClosePauseMenu_Implementation()
{
	ClosePauseMenu();
}

void UUW_PauseMenu::ClosePauseMenu()
{
	RemoveFromParent();
}

void UUW_PauseMenu::ReceivedAnswer_NewGame(bool Answer)
{
	check(DialogFrame);
	DialogFrame->OnReceivedAnswerEvent.RemoveDynamic(this, &ThisClass::ReceivedAnswer_NewGame);
	if (Answer)
	{
		UralJam_GameInstance->StartNewSession();
		Pre_ClosePauseMenu();
	}
	else
	{
		HiddenDialog();
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
