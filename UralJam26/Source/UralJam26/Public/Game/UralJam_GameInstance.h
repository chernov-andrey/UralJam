// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Intrfaces/Managment_Missions.h"
#include "Data/PDA_Character_Events.h"
#include "UralJam_GameInstance.generated.h"

class UUserWidget;
class USettings_SaveGame;
class UProgress_SaveGame;
class AGame_PlayerController;
class UUW_Cutscene;
class UUW_SplashScreen;
class AEvent_Initiator_atMap;
class USoundMix;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangeSettingsSound, float, Value);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FChanged_GS);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FLoadedLevel, FName, LevelName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRemoveCutscene, ECutsceneID, ID);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FUnloadCurrentLevel);

	UENUM(BlueprintType)
		enum class EGameState : uint8
	{
		GS_Starting,
		GS_MainMenu,
		GS_Loading,
		GS_InGame,
		GS_Paused,
		GS_Cutscene,
		GS_LoadingLevel
	};

	UENUM(BlueprintType)
		enum class EInheritance : uint8
	{
		Death,
		Left,
		Win
	};

UCLASS()
class URALJAM26_API UUralJam_GameInstance : public UGameInstance, public IManagment_Missions
{
	GENERATED_BODY()

	
//============================================================================================================================================
//                                              GMAE STATE
//============================================================================================================================================
private:
	TMap<EGameState, bool> MapState;
	void InitMapState();

public:
	UPROPERTY(BlueprintReadOnly)
	bool bIsGameplayMod; // режим имено игры

	UFUNCTION(BlueprintCallable)
	bool IsGameState_state(EGameState state)const;

	UFUNCTION()
	void SetGameState_state(EGameState state, bool val);



//============================================================================================================================================
//                                              Events
//============================================================================================================================================
public:
	UPROPERTY(BlueprintAssignable)
	FRemoveCutscene OnEndCutsceneEvent;

	UPROPERTY(BlueprintAssignable)
	FChanged_GS OnChangedGameStateEvent;

	UPROPERTY(BlueprintAssignable)
	FLoadedLevel OnLevelLoadedEvent;

	UPROPERTY(BlueprintAssignable)
	FUnloadCurrentLevel OnUnloadCCurrentLevelEvent;

	UPROPERTY(BlueprintAssignable)
	FUnloadCurrentLevel OnShowPauseMenuEvent;

	UPROPERTY(BlueprintAssignable)
	FUnloadCurrentLevel  OnHiddenPauseMenuEvent;


//============================================================================================================================================
//                                             Control --
//============================================================================================================================================

public:
	virtual void Init() override;

	UFUNCTION()
	void StartNewSession();
	
	UFUNCTION() // Запуск Физики активация контроллера
	void StartPlay_NewLevel(FName NewLevelName);

	void SetPlayerController(TObjectPtr<AGame_PlayerController> lPlayerController);
	
	//void
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<AGame_PlayerController> PlayerController;

private:
	UPROPERTY(VisibleAnywhere)
	FName Current_UseStreamingLevel;
	
	UPROPERTY(VisibleAnywhere)
	ULevelStreaming* Current_LoadedStreamingLevel;

	


	//============================================================================================================================================
	//                                              LEVELS management
	//============================================================================================================================================
	UFUNCTION()
	void OnUnloadLevel(int32 linkage);

	UFUNCTION()
	void Load_NewLevel(FName NewLevelName);
	

public:
	UFUNCTION(BlueprintCallable)
	void Launch_NewLevel(FName NewLevelName, int Index_Hero);
private:
	UFUNCTION()
	void LoadedLevel(int32 Linkage);
	
	UFUNCTION()
	void StartLoadAsyncLevel(FName LevelName);
	


	//============================================================================================================================================
	//                                                   Settings
	//============================================================================================================================================


	//--------------------------------------------------- Settings -------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void SaveSettings();

	UFUNCTION(BlueprintCallable, Category = "Game | Save/Load")
	void LoadSettings();

	UFUNCTION(BlueprintCallable, Category = "Game |  Settings")
	void ApplySettings();
	


	

	//-------------------------------------------------- Audio --------------------------------------
public:
	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	void SetMasterVolume(float newVolume);

	UFUNCTION(BlueprintCallable, Category = "Game | Settings")
	float GetMasterVolume()const;
protected:

	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	TObjectPtr<USoundMix> MasterSoundMix;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	USoundClass* Master_SoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	USoundClass* UI_Effects_SoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	USoundClass* Music_SoundClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Settings")
	USoundClass* Game_Effects_SoundClass;

	UPROPERTY(BlueprintAssignable)
	FChangeSettingsSound OnChangesSettingSoundEvent;
	//============================================================================================================================================
	//                                              Media management
	//============================================================================================================================================

	//---------------------------------------------- Splash Screen --------------------------------------------

public:
	UFUNCTION()
	void CreateSplashScreen_Widget();
	UFUNCTION()
	void RemoveSplashScreen_Widget();

private:
	UPROPERTY()
	TObjectPtr<UUW_SplashScreen> SplashScreen_Widget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUW_SplashScreen> WidgetType_SplashScreen;


	//---------------------------------------------- Pause Menu --------------------------------------------


public:
	UFUNCTION(BlueprintCallable)
	void OpenClosePauseMenu();

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> PauseMenu;

	UFUNCTION()
	void HiddenPauseMenu();
	UFUNCTION()
	void ShowPauseMenu();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> WidgetType_PauseMenu;


	//----------------------------------------------- Main Menu ------------------------------------------

public:
	UFUNCTION(BlueprintCallable)
	void CreateMainMenu_Widget();
	UFUNCTION()
	void RemoveMainMenu_Widget();

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> MainMenu_Widget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> WidgetType_MainMenu;


	//--------------------------------------------- Loading Screen ------------------------------------------------

public:

	UFUNCTION()
	void CreateLoadingScreen_Widget();
	UFUNCTION()
	void RemoveLoadingScreen_Widget();

private:
	UPROPERTY()
	TObjectPtr<UUserWidget> LoadingScreen_Widget;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Widgets")
	TSubclassOf<UUserWidget> WidgetType_LoadingScreen;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Settings Controller Game_PlayerController | Settings view widgets",
		meta = (ClampMin = "1.0", ClampMax = "15.0",
			UIMin = "1.0", UIMax = "15.0"))
	float MinLifeTime_LoadingScreen = 2.0f;
	
	
	//--------------------------------------------- Cutscene ---------------------------------------------------------

public:
	UFUNCTION(BlueprintCallable)// Создаем виджет катсцены 
	void LaunchCutscene(ECutsceneID ID);
	
	UFUNCTION()
	void EndLaunchCutscene(UUW_Cutscene* CutscenePtr);

private:
	UPROPERTY()
	TObjectPtr<UUW_Cutscene> Cutscene_Widget;


	//============================================================================================================================================
	//                                              NAMES
	//============================================================================================================================================
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Maps")
	TArray<FName> Levels_is_Linkage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game |  Maps")
	TArray<FName> TargetPoint_Tag;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotProgress = TEXT("Progress");

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game | Save/Load")
	FString SaveSlotSettings = TEXT("Settings");





	




	




	//--------------------------------------------------- Save fails -------------------------------------

private:
	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<USettings_SaveGame> Settings;

	UPROPERTY(VisibleAnywhere, Category = "Game | Settings")
	TObjectPtr<UProgress_SaveGame> Progress;


	//--------------------------------------------------- Select Hero --------------------------------------

public:
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game | Characters")
	TArray<TSubclassOf<AMaster_Character>> ListClassHero;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int CurrentClassHero;



	//============================================================================================================================================
	//                                             INTERFACES
	//============================================================================================================================================

	//--------------------------------------------- Management_Missions --------------------------------------
	
public:
virtual void CreateNewMission_Implementation(EMissionID ID) override;
virtual void CreateQuest_GoTo_Implementation(EMissionID ID, AEvent_Initiator_atMap* InitiatorActor) override;
virtual void CreateQuest_KillAll_Implementation(EMissionID ID, int CountLiveEnemy) override;
virtual void UpdateQuest_KillAll_Implementation(EMissionID ID, int CountLiveEnemy) override;





//============================================================================================================================================
//                                             INTERFACES
//============================================================================================================================================



UPROPERTY( BlueprintReadWrite)
 EInheritance InheritanceFather;


};
