// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\UralJam_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "SavesObjects\Progress_SaveGame.h"
#include "SavesObjects\Settings_SaveGame.h"
#include "Engine/LevelStreaming.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundClass.h"

void UUralJam_GameInstance::Init()
{
	Super::Init();
	GameState = EGameState::GS_Starting;
	LoadSettings();
	LoadProgress();
	StartLoadAsyncLevel(Level_1_Name, 1);
}

void UUralJam_GameInstance::SetPlayerController(TObjectPtr<AGame_PlayerController> lPlayerController)
{
	PlayerController = lPlayerController;
}

//Load level  -------------------------------------------------------------------------------------------

void UUralJam_GameInstance::StartLoadAsyncLevel(FName LevelName, int32 Linkage)
{
	if (UWorld* World = GetWorld())
	{
	check(LevelName.IsValid()&&"UUralJam_GameInstance::StartLoadAsyncLevel: Level name is invalid");
	FLatentActionInfo LatentActionInfo;
	LatentActionInfo.ExecutionFunction = "LoadedLevel";
	LatentActionInfo.CallbackTarget = this;
	LatentActionInfo.Linkage = Linkage;
	LatentActionInfo.UUID = GetUniqueID();

		 UGameplayStatics::LoadStreamLevel(World, LevelName, false, false, LatentActionInfo);
		 UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::StartLoadAsyncLevel:Start load level -%s!"), *LevelName.ToString());
	}
}

// Level is loaded  -------------------------------------------------------------------------------------------

void  UUralJam_GameInstance::LoadedLevel(int32 i)
{
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: function triggered"));
	FName LoadedLevelName;
	switch (i) {
	case 1:
		LoadedLevelName = Level_1_Name;
		break;
	case 2:
		LoadedLevelName = Level_2_Name;
		break;
	default: 
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadedLevel: function triggered for unknow Linkage"));
		break;
	}
		ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, LoadedLevelName);
		if (LevelStreaming->IsLevelLoaded())
		{
			UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is loaded"), *LoadedLevelName.ToString());
			OnLevelLoadedEvent.Broadcast();
		}
}

//PROGRESS  -------------------------------------------------------------------------------------------
// Загружаем сохраненный прогресс и если есть запись о пршлой игре подгружаем уровень

void UUralJam_GameInstance::LoadProgress()
{
	
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotProgress, 0))
	{
		Progress = Cast< UProgress_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotProgress, 0));
		if (Progress)
		{
			UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadProgress: success load Progress!"));

			FName NameLevel = Progress->LevelForContinue_Name;
			if (NameLevel == Level_1_Name)
			{
				return;
			}
			if (NameLevel == Level_2_Name)
			{
				StartLoadAsyncLevel(NameLevel, 2);
				return;
			}
			UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::LoadProgress: unknow level name!"));
		}
		
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::LoadProgress: Error load save Progress! but there save"));
	}
	else
	{
		Progress = Cast< UProgress_SaveGame>(UGameplayStatics::CreateSaveGameObject(UProgress_SaveGame::StaticClass()));

		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadProgress: fail load Progress!(not found save) "));
	}
}
void UUralJam_GameInstance::SaveProgress() 
{
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::SaveProgress(): TRY SAVEGAME!"));
	UGameplayStatics::SaveGameToSlot(Progress, SaveSlotProgress, 0);
}


void  UUralJam_GameInstance::StartNewGame() // нажата кнопка в меню и она вызывает 
{
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::StartNewGame"));
	SetGameState_state(EGameState::GS_Loading);
	CreateLoadingScreen_Widget();
	RemoveMainMenu_Widget();
	//PlayerController;////////////// говорим сонтроллеру подготовься
	
		ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, Level_1_Name);
	if (LevelStreaming->IsLevelLoaded())
	{
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is loaded"), *Level_1_Name.ToString());
		LevelStreaming->SetShouldBeVisible(true);		
	}
}
void UUralJam_GameInstance::StartContinueGame()
{
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::StartContinueGame"));

}




// SETTINGS -------------------------------------------------------------------------------------------

void UUralJam_GameInstance::LoadSettings()
{
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotSettings, 0))
	{
		Settings = Cast< USettings_SaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotSettings, 0));
		
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
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::SaveSettings: TRY SAVEGAME!"));
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

// Audio volume  -------------------------------------------------------------------------------------------

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


// checking the readiness of levels -------------------------------------------------------------------------------------------
 

bool UUralJam_GameInstance::CanContinueGame() const
{
	if (Progress)
	{
		if (!Progress->bIsNewGame) 
		{		
			FName NameLevel = Progress->LevelForContinue_Name;		
			ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, NameLevel);
			if (LevelStreaming->IsLevelLoaded())
			{
				return true;
				UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::CanContinueGame: Can continue game! "));
			}	
		}
	}	

	UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::CanContinueGame: Can't continue game! "));
	return false;
}
bool UUralJam_GameInstance::CanNewGame() const
{
	ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(this, Level_1_Name);
	if (LevelStreaming->IsLevelLoaded())
	{
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::CanContinueGame: Can continue game! "));
		return true;
	}
	return false;
}


// checking Game state -------------------------------------------------------------------------------------------


bool UUralJam_GameInstance::IsGameState_state(EGameState State) const
{
	return( GameState == State);
}

void UUralJam_GameInstance::SetGameState_state(EGameState State) 
{
	GameState = State;
}


// Loading Screen ------------------------------------------------------------------------------------------


void UUralJam_GameInstance::CreateLoadingScreen_Widget()
{
	if (!TimerHandle_LifeLoadingWidget.IsValid())
	{
		check(WidgetType_LoadingScreen);
		LoadingScreen_Widget = CreateWidget(this, WidgetType_LoadingScreen);
		LoadingScreen_Widget->AddToViewport();
		GetWorld()->GetTimerManager().SetTimer(TimerHandle_LifeLoadingWidget, this, &UUralJam_GameInstance::RemoveLoadingScreen_Widget, MinLifeTime_LoadingScreen, false);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::CreateLoadingScreen_Widget: It cannot be completed now!"));
	}
}
void UUralJam_GameInstance::RemoveLoadingScreen_Widget()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LifeLoadingWidget);
	if (LoadingScreen_Widget)
	{
		LoadingScreen_Widget->RemoveFromParent();
	}

	SetGameState_state(EGameState::GS_InGame);

	OnGameStartedEvent.Broadcast();
}



// Splash Screen ------------------------------------------------------------------------------------------




void UUralJam_GameInstance::CreateSplashScreen_Widget()
{
	if ( !TimerHandle_LifeSplashWidget.IsValid())
	{
		check(WidgetType_SplashScreen);

		SplashScreen_Widget = CreateWidget(this, WidgetType_SplashScreen);
		SplashScreen_Widget->AddToViewport();

		GetWorld()->GetTimerManager().SetTimer(TimerHandle_LifeSplashWidget, this, &UUralJam_GameInstance::RemoveSplashScreen_Widget, LifeTime_SplashScreen, false);	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::CreateLoadingScreen_Widget: It cannot be completed now!"));
	}
}
void UUralJam_GameInstance::RemoveSplashScreen_Widget()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerHandle_LifeSplashWidget);
	if (SplashScreen_Widget)
	{
		SplashScreen_Widget->RemoveFromParent();
	}

	SetGameState_state(EGameState::GS_MainMenu);
	
}


// Pause menu ------------------------------------------------------------------------------------------


void UUralJam_GameInstance::OpenClosePauseMenu()
{/*
	if (IsPaused())
	{
		UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::PauseFlipFlop : Pause = false"));
		SetPause(false);
		if (HiddenPauseMenu())
		{
			SetInputMode(FInputModeGameOnly());
			bShowMouseCursor = false;
		}
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::PauseFlipFlop : Pause = true"));
		SetPause(true);
		if (ShowPauseMenu())
		{
			SetInputMode(FInputModeGameAndUI());
			bShowMouseCursor = true;
		}
	}*/
}
void UUralJam_GameInstance::HiddenPauseMenu()
{
	if (PauseMenu)
	{
		PauseMenu->RemoveFromParent();
		PauseMenu = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT(" UUralJam_GameInstance::HiddenPauseMenu: attempt to close a missing widget"));
	}
}
void UUralJam_GameInstance::ShowPauseMenu()
{
	check(WidgetType_PauseMenu);
	if (!PauseMenu)
	{
		PauseMenu = CreateWidget<UUserWidget>(this, WidgetType_PauseMenu);
	}
	if (PauseMenu)
	{
		PauseMenu->AddToViewport();
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT(" UUralJam_GameInstance::ShowPauseMenu: couldn't create widget PauseMenu"));
	}
}


// Main menu ------------------------------------------------------------------------------------------

void UUralJam_GameInstance::CreateMainMenu_Widget()
{
	check(WidgetType_MainMenu);

	MainMenu_Widget = CreateWidget(this, WidgetType_MainMenu);
	MainMenu_Widget->AddToViewport();
}

void UUralJam_GameInstance::RemoveMainMenu_Widget()
{
	if (MainMenu_Widget)
	{
		MainMenu_Widget->RemoveFromParent();
	}
}

