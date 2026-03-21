// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\UralJam_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Widgets/UW_Cutscene.h"
#include "Widgets/UW_SplashScreen.h"
#include "Widgets/UW_LoadingScreen.h"
#include "Game\Game_PlayerController.h"
#include "SavesObjects\Progress_SaveGame.h"
#include "SavesObjects\Settings_SaveGame.h"
#include "Engine/LevelStreaming.h"
#include "Blueprint/UserWidget.h"
#include "Sound/SoundClass.h"

void UUralJam_GameInstance::Init()
{
	InitMapState();
	Super::Init();
	SetGameState_state(EGameState::GS_Starting,true);
	LoadSettings();


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
	case 11:
		LoadedLevelName = Level_1_Name;
		if (UGameplayStatics::GetStreamingLevel(GetWorld(), Level_1_Name)->IsLevelLoaded())
		{
			OnFirstLevelLoadedEvent.Broadcast();
		}
		break;
	case 21:
		LoadedLevelName = Level_2_Name;
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadedLevel: function triggered for unknow Linkage"));
		return;
		break;
	}
	ULevelStreaming* LevelStreaming = UGameplayStatics::GetStreamingLevel(GetWorld(), LoadedLevelName);
	if (LevelStreaming && LevelStreaming->IsLevelLoaded()) 
	{
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is loaded"), *LoadedLevelName.ToString());
		LevelStreaming->SetShouldBeVisible(true);	
		Current_StreamingLevel = LevelStreaming;
	}
	
}




void  UUralJam_GameInstance::StartPlay() // Начало новой игры
{
	OnFirstLevelLoadedEvent.RemoveDynamic(this, &UUralJam_GameInstance::StartPlay);
}
void  UUralJam_GameInstance::ReloadFirstLevel(int32 i)
{
	if (i == 10)
	{
		StartLoadAsyncLevel(Level_1_Name, 11);
	}
}

void  UUralJam_GameInstance::StartNewSession() // Начало новой cсессии
{
	
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::StartNewSession"));
	
	LaunchCutscene(WidgetType_1_Cutscene);
	CreateLoadingScreen_Widget();

	RemoveMainMenu_Widget();
	RemoveMainMenu_Widget();
	OnFirstLevelLoadedEvent.AddDynamic(this, &UUralJam_GameInstance::StartPlay);
	OnFirstLevelLoadedEvent.AddDynamic(this,&UUralJam_GameInstance::RemoveLoadingScreen_Widget);
	ULevelStreaming* FirstLevelStreaming = UGameplayStatics::GetStreamingLevel(GetWorld(), Level_1_Name);

	if (Current_StreamingLevel == nullptr) // если нет текущего загркженного уровня то просто загружаем первый уровень
	{
		StartLoadAsyncLevel(Level_1_Name, 11);
	}
	else  // мы на какомто уровне
	{
		
		if (FirstLevelStreaming->IsLevelLoaded())
		{
			check(FirstLevelStreaming == Current_StreamingLevel);
			Current_StreamingLevel = nullptr;
			
			FLatentActionInfo LatentActionInfo;
			LatentActionInfo.ExecutionFunction = "ReloadFirstLevel";
			LatentActionInfo.CallbackTarget = this;
			LatentActionInfo.Linkage = 10;
			LatentActionInfo.UUID = GetUniqueID();
			UGameplayStatics::UnloadStreamLevel(GetWorld(), Level_1_Name, LatentActionInfo, true);
		}
		else  // мы не на 1 уровне
		{
			if (Current_StreamingLevel->IsLevelLoaded())
			{
				StartLoadAsyncLevel(Level_1_Name, 11);
				UGameplayStatics::UnloadStreamLevel(GetWorld(), Current_StreamingLevel->GetFName(), FLatentActionInfo(), true);
				Current_StreamingLevel = nullptr;
			}
			else 
			{
					check(false&& "UUralJam_GameInstance::StartNewSession: CurrentLevel != nuulptr but CurrentLevel not load ");
			}
		}
	}

	if (!PlayerController->TeleportToTargetPoint(TargetPoint_Tag_1))
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::StartNewSession  -> PlayerController->TeleportToTargetPoint(TargetPoint_Tag_1)   -  FAIL"));
	}
}
c
{


}



//=============================================================================================================================================================


// Game STATE -------------------------------------------------------------------------------------------

void UUralJam_GameInstance::InitMapState()
{
	MapState.Add(EGameState::GS_Starting, false);
	MapState.Add(EGameState::GS_Cutscene, false);
	MapState.Add(EGameState::GS_InGame, false);
	MapState.Add(EGameState::GS_Loading, false);
	MapState.Add(EGameState::GS_MainMenu, false);
	MapState.Add(EGameState::GS_Paused, false);
}
bool UUralJam_GameInstance::IsGameState_state(EGameState State) const
{
	return MapState[State];
}
void UUralJam_GameInstance::SetGameState_state(EGameState State,bool val)
{
	MapState.Add( State,val);
}




//=============================================================================================================================================================


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

// Pause menu ------------------------------------------------------------------------------------------

void UUralJam_GameInstance::OpenClosePauseMenu()
{
	if (IsGameState_state(EGameState::GS_Paused))
	{
		SetGameState_state(EGameState::GS_Paused,false);
		UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::PauseFlipFlop : New game state - GS_InGame"));
		
		PlayerController->SetPause(false);
		
		HiddenPauseMenu();	
	}
	else 
	{
		SetGameState_state(EGameState::GS_Paused,true);
		UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::PauseFlipFlop : New game state - GS_Paused"));
		
		PlayerController->SetPause(true);
		
		ShowPauseMenu();
	}
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

// Splash Screen ------------------------------------------------------------------------------------------

void UUralJam_GameInstance::CreateSplashScreen_Widget()
{
		check(WidgetType_SplashScreen);

		SplashScreen_Widget = Cast<UUW_SplashScreen>(CreateWidget(this, WidgetType_SplashScreen));
		SplashScreen_Widget->AddToViewport();
		SplashScreen_Widget->OnCloseSplashScreenEvent.AddDynamic(this, &UUralJam_GameInstance::RemoveSplashScreen_Widget);
}
void UUralJam_GameInstance::RemoveSplashScreen_Widget()
{
	if (SplashScreen_Widget)
	{
		SplashScreen_Widget->RemoveFromParent();
	}	
}

// Loading Screen ------------------------------------------------------------------------------------------

void UUralJam_GameInstance::CreateLoadingScreen_Widget()
{
	SetGameState_state(EGameState::GS_Loading, true);
	if (LoadingScreen_Widget==nullptr)
	{
		check(WidgetType_LoadingScreen);
		LoadingScreen_Widget = CreateWidget(this, WidgetType_LoadingScreen);
		LoadingScreen_Widget->AddToViewport();	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::CreateLoadingScreen_Widget: It cannot be completed now!"));
	}
}
void UUralJam_GameInstance::RemoveLoadingScreen_Widget()
{
	OnFirstLevelLoadedEvent.RemoveDynamic(this, &UUralJam_GameInstance::RemoveLoadingScreen_Widget);

	if (LoadingScreen_Widget)
	{
		Cast< UUW_LoadingScreen>(LoadingScreen_Widget)->Deferred_RemoveFromParent();
	
		LoadingScreen_Widget = nullptr;
	}
	SetGameState_state(EGameState::GS_Loading, false);
}

// Cutscene -------------------------------------------------------------------------------------------

void  UUralJam_GameInstance::LaunchCutscene(TSubclassOf<UUW_Cutscene> ClassCutsceneWidget)
{
	SetGameState_state(EGameState::GS_Cutscene,true);
	PlayerController->DeactivationController();
	Cutscene_Widget = Cast<UUW_Cutscene>(CreateWidget(this, ClassCutsceneWidget));
	Cutscene_Widget->AddToViewport();
	PlayerController->OnSkipCutsceneEvent.AddDynamic(Cutscene_Widget, &UUW_Cutscene::SkipCutscene);
	
	Cutscene_Widget->OnEndCutsceneEvent.AddDynamic(this, &UUralJam_GameInstance::EndLaunchCutscene);
}
void  UUralJam_GameInstance::EndLaunchCutscene(UUW_Cutscene* CutscenePtr)
{
	PlayerController->OnSkipCutsceneEvent.RemoveDynamic(CutscenePtr, &UUW_Cutscene::SkipCutscene);
	CutscenePtr->RemoveFromParent();
	SetGameState_state(EGameState::GS_Cutscene,false);
	PlayerController->ActivationController();
}


//=============================================================================================================================================================


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
