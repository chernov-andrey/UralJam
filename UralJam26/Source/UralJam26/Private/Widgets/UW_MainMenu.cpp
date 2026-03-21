// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets\UW_MainMenu.h"
#include "Game\UralJam_GameInstance.h"
#include "Components\Button.h"
#include "Components\Slider.h"

void UUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ExitGameButton)
	{
		ExitGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnExitGameButtonClicked);
	}
	if (SoundVolumeSlider)
	{
		SoundVolumeSlider->OnValueChanged.AddDynamic(this,&UUW_MainMenu::OnMasterVolumeChanged);
	}
	// из GmaeInstanse получаем информацию для настройки виджета
	UralJam_GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	if (UralJam_GameInstance)
	{
		SoundVolumeSlider->SetValue(UralJam_GameInstance->GetMasterVolume());
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("UUW_MainMenu::NativeConstruct: UralJam_GameInstance is invalid!"));
	}

}




// Updates state buttons -------------------------------------------------------------------------------------------------------


void UUW_MainMenu::StartNewGame()
{
	if (UralJam_GameInstance)
	{
		UralJam_GameInstance->StartNewSession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu::StartNewGame: UralJam_GameInstance not found!"));
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

