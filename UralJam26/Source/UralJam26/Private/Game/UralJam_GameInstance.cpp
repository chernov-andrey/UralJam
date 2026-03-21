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




//Load level  -----------------------------------------------------------------------------------------------

void UUralJam_GameInstance::StartLoadAsyncLevel(FName LevelName)
{
	if (UWorld* World = GetWorld())
	{
		check(LevelName.IsValid() && UGameplayStatics::GetStreamingLevel(World, LevelName) && "UUralJam_GameInstance::StartLoadAsyncLevel: Level name is invalid");
	
		FLatentActionInfo LatentActionInfo;
		LatentActionInfo.ExecutionFunction = "LoadedLevel";
		LatentActionInfo.CallbackTarget = this;
		LatentActionInfo.Linkage = Levels_is_Linkage.Find(LevelName);
		LatentActionInfo.UUID = GetUniqueID();

		UGameplayStatics::LoadStreamLevel(World, LevelName, false, false, LatentActionInfo);
		 UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::StartLoadAsyncLevel:Start load level -%s!"), *LevelName.ToString());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::StartLoadAsyncLevel: GetWorld()- FAIL!"));
	}
}

// Level is loaded  -------------------------------------------------------------------------------------------

void  UUralJam_GameInstance::LoadedLevel(int32 Linkage)
{
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: function triggered"));
	
	if (Levels_is_Linkage.IsValidIndex(Linkage))
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadedLevel: invalid index for Levels-is_linkage"));
	}
	Current_UseStreamingLevel = UGameplayStatics::GetStreamingLevel(GetWorld(), Levels_is_Linkage[0]);
	if (Current_UseStreamingLevel && Current_UseStreamingLevel->IsLevelLoaded())
	{
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is loaded"), *Levels_is_Linkage[0].ToString());
		Current_UseStreamingLevel->SetShouldBeVisible(true);
		OnLevelLoadedEvent.Broadcast(Levels_is_Linkage[0]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is not found or level is not loaded"),*Levels_is_Linkage[0].ToString());
	}
	
}




void  UUralJam_GameInstance::StartPlay_NewLevel(FName NewLevelName) // Начало новой игры
{
	//OnFirstLevelLoadedEvent.RemoveDynamic(this, &UUralJam_GameInstance::StartPlay_NewLevel);
	auto index =Levels_is_Linkage.Find(NewLevelName);
	RemoveLoadingScreen_Widget();
	if (WidgetTypes_Cutscenes.IsValidIndex(index))
	{
		if (WidgetTypes_Cutscenes[index] != nullptr)
		{
			LaunchCutscene(WidgetTypes_Cutscenes[index]);
		
		}
	}
	if (!PlayerController->TeleportToTargetPoint(TargetPoint_Tag_1))
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::StartNewSession  -> PlayerController->TeleportToTargetPoint(TargetPoint_Tag_1)   -  FAIL"));
	}
}




void  UUralJam_GameInstance::Load_NewLevel(FName NewLevelName)// загружаем уровень когда очистили от старого
{
	OnLevelLoadedEvent.AddDynamic(this, &UUralJam_GameInstance::StartPlay_NewLevel);
	StartLoadAsyncLevel(NewLevelName);
	
}

void UUralJam_GameInstance::OnUnloadLevel(int32 Linkage)
{
	if (Levels_is_Linkage.IsValidIndex(Linkage))
	{
		Load_NewLevel(Levels_is_Linkage[Linkage]);			
	}
	else 
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::OnUnloadLevel:  Invalid index for Levels_is_Linkage"));
	}
}


void  UUralJam_GameInstance::Launch_NewLevel(FName NewLevelName) // start transition level
{
	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::PlayNewlevel"));
	CreateLoadingScreen_Widget();
	if(MainMenu_Widget!= nullptr)
	{
		RemoveMainMenu_Widget();
	}
	
	if (Current_UseStreamingLevel != nullptr)
	{
		FLatentActionInfo LatentActionInfo;
		LatentActionInfo.ExecutionFunction = "OnUnloadLevel";  /////  
		LatentActionInfo.CallbackTarget = this;
		LatentActionInfo.Linkage = Levels_is_Linkage.Find(NewLevelName);
		LatentActionInfo.UUID = GetUniqueID();
		if ( Current_UseStreamingLevel->IsLevelLoaded())
		{
			UGameplayStatics::UnloadStreamLevel(GetWorld(), Current_UseStreamingLevel->GetFName(), LatentActionInfo, true);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" UUralJam_GameInstance::Launch_NewLevel: Current_UseStreamingLevel - is not nullptr! But *Current_UseStreamingLevel is not loaded!"));
			Load_NewLevel(NewLevelName);
		}
			Current_UseStreamingLevel = nullptr;
	}
	else 
	{
		Load_NewLevel(NewLevelName);
	}

}



//=============================================================================================================================================================

void UUralJam_GameInstance::StartNewSession()
{
	Launch_NewLevel(Levels_is_Linkage[0]);
}

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
		LoadingScreen_Widget->AddToViewport(5);	
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
