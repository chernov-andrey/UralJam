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
#include "Game\Master_Character.h"
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
		check(LevelName.IsValid() && UGameplayStatics::GetStreamingLevel(World, LevelName) && "UUralJam_GameInstance::StartLoadAsyncLevel: Level name is invalid or level is already uploaded ");
	
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
	
	if (!Levels_is_Linkage.IsValidIndex(Linkage))
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadedLevel: invalid index for Levels-is_linkage"));
	}
	Current_UseStreamingLevel = Levels_is_Linkage[Linkage];
	ULevelStreaming* LevelS	= UGameplayStatics::GetStreamingLevel(GetWorld(), Current_UseStreamingLevel);
	if (LevelS && LevelS->IsLevelLoaded())
	{
		UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is loaded"), *Levels_is_Linkage[0].ToString());
		LevelS->SetShouldBeLoaded(true);
		LevelS->SetShouldBeVisible(true);
		
		OnLevelLoadedEvent.Broadcast(Levels_is_Linkage[Linkage]);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::LoadedLevel: %s - is not found or level is not loaded"),*Levels_is_Linkage[0].ToString());
	}
	
}




void  UUralJam_GameInstance::StartPlay_NewLevel(FName NewLevelName) // Начало новой игры
{
	OnLevelLoadedEvent.RemoveDynamic(this, &UUralJam_GameInstance::StartPlay_NewLevel);

	if (!PlayerController->TeleportToTargetPoint(TargetPoint_Tag[Levels_is_Linkage.Find(NewLevelName)]))
	{
		UE_LOG(LogTemp, Error, TEXT("UUralJam_GameInstance::StartNewSession  -> PlayerController->TeleportToTargetPoint(TargetPoint_Tag[Levels_is_Linkage.Find(NewLevelName)])   -  FAIL"));
	}
	RemoveLoadingScreen_Widget();

	SetGameState_state(EGameState::GS_LoadingLevel, false);
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
	SetGameState_state(EGameState::GS_LoadingLevel, true);

	UE_LOG(LogTemp, Display, TEXT("UUralJam_GameInstance::PlayNewlevel"));
	CreateLoadingScreen_Widget();
	if(MainMenu_Widget!= nullptr)
	{
		RemoveMainMenu_Widget();
	}
	
	if (Current_UseStreamingLevel != FName())
	{

		FLatentActionInfo LatentActionInfo;
		LatentActionInfo.ExecutionFunction = "OnUnloadLevel";  /////  
		LatentActionInfo.CallbackTarget = this;
		LatentActionInfo.Linkage = Levels_is_Linkage.Find(NewLevelName);
		LatentActionInfo.UUID = GetUniqueID();
		
		ULevelStreaming* LevelS = UGameplayStatics::GetStreamingLevel(GetWorld(), Current_UseStreamingLevel);
		
		if (LevelS->IsLevelLoaded())
		{
			UGameplayStatics::UnloadStreamLevel(GetWorld(), Current_UseStreamingLevel, LatentActionInfo, false);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT(" UUralJam_GameInstance::Launch_NewLevel: Current_UseStreamingLevel - is not nullptr! But *Current_UseStreamingLevel is not loaded!"));
			Load_NewLevel(NewLevelName);
		}
			Current_UseStreamingLevel = FName();
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
	MapState.Add(EGameState::GS_LoadingLevel, false);
}
bool UUralJam_GameInstance::IsGameState_state(EGameState State) const
{
	return MapState[State];
}
void UUralJam_GameInstance::SetGameState_state(EGameState State,bool val)
{
	MapState.Add( State,val);
	if (IsGameState_state(EGameState::GS_Cutscene) || IsGameState_state(EGameState::GS_Starting) || IsGameState_state(EGameState::GS_Loading) 
		|| IsGameState_state(EGameState::GS_MainMenu) || IsGameState_state(EGameState::GS_Paused)|| IsGameState_state(EGameState::GS_LoadingLevel))
	{
		if (bIsGameplayMod) 
		{
			bIsGameplayMod = false;
			OnChangedGameStateEvent.Broadcast();
		}
	}
	else
	{
		if (!bIsGameplayMod)
		{
			bIsGameplayMod = true;
			OnChangedGameStateEvent.Broadcast();
		}
	}

}




//=============================================================================================================================================================


// Main menu ------------------------------------------------------------------------------------------

void UUralJam_GameInstance::CreateMainMenu_Widget()
{
	SetGameState_state(EGameState::GS_MainMenu, true);
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
	SetGameState_state(EGameState::GS_MainMenu, false);
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
		PauseMenu->AddToViewport(6);
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
		SplashScreen_Widget->AddToViewport(10);
		SplashScreen_Widget->OnCloseSplashScreenEvent.AddDynamic(this, &UUralJam_GameInstance::RemoveSplashScreen_Widget);
}
void UUralJam_GameInstance::RemoveSplashScreen_Widget()
{
	if (SplashScreen_Widget)
	{
		SplashScreen_Widget->RemoveFromParent();
	}	
	SetGameState_state(EGameState::GS_Starting, false);
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
	

	if (LoadingScreen_Widget)
	{
		Cast< UUW_LoadingScreen>(LoadingScreen_Widget)->Deferred_RemoveFromParent();
	
		LoadingScreen_Widget = nullptr;
	}
	SetGameState_state(EGameState::GS_Loading, false);
}

// Cutscene -------------------------------------------------------------------------------------------

void  UUralJam_GameInstance::LaunchCutscene(ECutsceneID ID)
{
	SetGameState_state(EGameState::GS_Cutscene,true);
	PlayerController->DeactivationController();

	AMaster_Character* Character = Cast<AMaster_Character>(PlayerController->GetCharacter());
	if (Character)
	{

		check(Character->DA_events && "UUralJam_GameInstance::StartPlay_NewLevel: AMaster_Character->DA_events - is NULL")
		
		TSubclassOf<UUW_Cutscene>ClassCutsceneWidget =Character->DA_events->ListCutscenes[ID];
	
		check(ClassCutsceneWidget && "UUralJam_GameInstance::LaunchCutscene: ClassCutsceneWidget - is invalid");
	
		Cutscene_Widget = Cast<UUW_Cutscene>(CreateWidget(this, ClassCutsceneWidget));
		Cutscene_Widget->OnEndCutsceneEvent.AddDynamic(this, &UUralJam_GameInstance::EndLaunchCutscene);

		Cutscene_Widget->ID = ID;
		Cutscene_Widget->AddToViewport();
		PlayerController->OnSkipCutsceneEvent.AddDynamic(Cutscene_Widget, &UUW_Cutscene::SkipCutscene);
	
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT(" UUralJam_GameInstance::StartPlay_NewLevel:  Cast<AMaster_Character>(PlayerController->GetCharacter()   -  FAIL"));
	}
}
void  UUralJam_GameInstance::EndLaunchCutscene(UUW_Cutscene* CutscenePtr)
{
	PlayerController->OnSkipCutsceneEvent.RemoveDynamic(CutscenePtr, &UUW_Cutscene::SkipCutscene);
	OnEndCutsceneEvent.Broadcast(CutscenePtr->ID);
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


//============================================================================================================================================
//                                             INTERFACES
//============================================================================================================================================

//--------------------------------------------- Management_Missions --------------------------------------



void UUralJam_GameInstance::CreateNewMission_Implementation(EMissionID ID)
{

	IManagment_Missions* Interface = Cast<IManagment_Missions>(PlayerController);
	if (Interface)
	{
		Interface->Execute_CreateNewMission(PlayerController, ID);
		
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::CreateNewMission: PlayerController hasnt interface  -IManagment_Missions "));
	}
}
void UUralJam_GameInstance::CreateQuest_GoTo_Implementation(EMissionID ID, AEvent_Initiator_atMap* InitiatorActor)
{

	IManagment_Missions* Interface = Cast<IManagment_Missions>(PlayerController);
	if (Interface)
	{
		Interface->Execute_CreateQuest_GoTo(PlayerController, ID, InitiatorActor);

	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::CreateQuest_GoTo_Implementation: PlayerController hasnt interface  -IManagment_Missions "));
	}

}
