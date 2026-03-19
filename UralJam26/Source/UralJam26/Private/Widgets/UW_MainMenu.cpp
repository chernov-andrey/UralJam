// Fill out your copyright notice in the Description page of Project Settings.


#include "Widgets\UW_MainMenu.h"
#include "Game\UralJam_GameInstance.h"
#include "Components\Button.h"
#include "Components\Slider.h"

void UUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartNewGameButton)
	{
		StartNewGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnStartNewGameButtonClicked);
	}
	/*if (ContinueGameButton)
	{
		ContinueGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnContinueGameButtonClicked);
	}*/
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
		if (!UralJam_GameInstance->CanNewGame())
		{
			if (StartNewGameButton)
			{
				StartNewGameButton->SetIsEnabled(false);
				UralJam_GameInstance->OnLevelLoadedEvent.AddDynamic(this, &UUW_MainMenu::UpdateState_StartNewGameButton);
			}
		}
		/*if (!UralJam_GameInstance->CanContinueGame())
		{
			if (ContinueGameButton)
			{
				ContinueGameButton->SetIsEnabled(false);
				UralJam_GameInstance->OnLevelLoadedEvent.AddDynamic(this,&UUW_MainMenu::UpdateState_ContinueGameButton);
			}
		}*/
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("UUW_MainMenu::NativeConstruct: UralJam_GameInstance is invalid!"));
	}

}

// Updates state buttons -------------------------------------------------------------------------------------------------------

void UUW_MainMenu::UpdateState_StartNewGameButton()
{
	if (UralJam_GameInstance)
	{
		if (UralJam_GameInstance->CanNewGame())
		{
			StartNewGameButton->SetIsEnabled(true);
			UralJam_GameInstance->OnLevelLoadedEvent.RemoveDynamic(this, &UUW_MainMenu::UpdateState_StartNewGameButton);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUW_MainMenu::UpdateState_StartNewGameButton: UralJam_GameInstance is invalid!"));
	}
}
/*
void UUW_MainMenu::UpdateState_ContinueGameButton()
{
	if (UralJam_GameInstance)
	{
		if (UralJam_GameInstance->CanContinueGame())
		{
			ContinueGameButton->SetIsEnabled(true);
			UralJam_GameInstance->OnLevelLoadedEvent.RemoveDynamic(this, &UUW_MainMenu::UpdateState_ContinueGameButton);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUW_MainMenu::UpdateState_ContinueGameButton: UralJam_GameInstance is invalid!"));
	}
}*/

// Decoupling(отвязка) from delegates -------------------------------------------------------------------------------------------------------

void UUW_MainMenu::DecouplingAll_forDelegate()
{
	if (UralJam_GameInstance)
	{
		if (UralJam_GameInstance->OnLevelLoadedEvent.IsAlreadyBound(this, &UUW_MainMenu::UpdateState_StartNewGameButton))
		{
			UralJam_GameInstance->OnLevelLoadedEvent.RemoveDynamic(this, &UUW_MainMenu::UpdateState_StartNewGameButton);
		}
		/*if (UralJam_GameInstance->OnLevelLoadedEvent.IsAlreadyBound(this, &UUW_MainMenu::UpdateState_ContinueGameButton))
		{
			UralJam_GameInstance->OnLevelLoadedEvent.RemoveDynamic(this, &UUW_MainMenu::UpdateState_ContinueGameButton);
		}*/
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUW_MainMenu::UpdateState_StartNewGameButton: UralJam_GameInstance is invalid!"));
	}
}


// Updates state buttons -------------------------------------------------------------------------------------------------------


void UUW_MainMenu::OnStartNewGameButtonClicked()
{
	if (UralJam_GameInstance)
	{
		DecouplingAll_forDelegate();
		UralJam_GameInstance->StartNewSession();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu: UralJam_GameInstance not found!"));
	}
}

/*
void UUW_MainMenu::OnContinueGameButtonClicked()
{
	if (UralJam_GameInstance)
	{
		check(false && "UUW_MainMenu::OnContinueGameButtonClicked: Logic load game not definition");
		DecouplingAll_forDelegate();
	// Логика продолжения игры	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUW_MainMenu::OnContinueGameButtonClicked: UralJam_GameInstance not found!"));
	}

}*/

void UUW_MainMenu::OnExitGameButtonClicked()
{

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		DecouplingAll_forDelegate();
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

