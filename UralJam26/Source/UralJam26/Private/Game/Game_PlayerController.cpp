// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\Game_PlayerController.h"
#include "InputAction.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet\GameplayStatics.h"
#include "Game\UralJam_GameInstance.h"

void AGame_PlayerController::BeginPlay()
{
    UralJam_GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
    if (UralJam_GameInstance)
    {
        if (UralJam_GameInstance->IsGameState_state(EGameState::GS_Starting)) 
        {
            MainMenu_Widget = CreateWidget(this, UralJam_GameInstance->GetClass_Widget_MainMenu());
            MainMenu_Widget->AddToViewport();
            CreateSplashScreen_Widget();
            UralJam_GameInstance->OnGameStartedEvent.AddDynamic(this,&ThisClass::);
        //привязаться для инициализации игрока
        }

    }else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::BeginPlay: FAIL CAST GameInstance to UralJam_GameInstance!"));
    }
    
    Super::BeginPlay();
}


// Management game mod  ------------------------------------------------------------------------------------------


void AGame_PlayerController::SetGameMod_InMenu()
{
    DisableInput(this);
    SetInputMode(FInputModeGameAndUI());
    bShowMouseCursor = true;
}

void AGame_PlayerController::SetGameMod_InGame()
{
    EnableInput(this);
    SetInputMode(FInputModeGameOnly());
    bShowMouseCursor = true;
}


// Temporary Widget ------------------------------------------------------------------------------------------


void AGame_PlayerController::CreateSplashScreen_Widget()
{
    if (UralJam_GameInstance &&  !TimerHandle_LifeTemporaryWidget.IsValid())
    {
        DisableInput(this);
        bShowMouseCursor = false;
        SetInputMode(FInputModeUIOnly());

        SplashScreen_Widget = CreateWidget(this, UralJam_GameInstance->GetClass_Widget_SplashScreen());
        SplashScreen_Widget->AddToViewport();
        GetWorldTimerManager().SetTimer(TimerHandle_LifeTemporaryWidget, this, &AGame_PlayerController::RemoveSplashScreen_Widget, LifeTime_SplashScreen, false);
        
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::CreateTemporaryWidget: It cannot be completed now!"));
    }
}
void AGame_PlayerController::RemoveSplashScreen_Widget()
{
    GetWorldTimerManager().ClearTimer(TimerHandle_LifeTemporaryWidget);
    if (SplashScreen_Widget)
    {
        SplashScreen_Widget->RemoveFromParent();
    }
 
    UralJam_GameInstance->SetGameState_state(EGameState::GS_MainMenu);
    bShowMouseCursor = true;
}





// Setup Input Component------------------------------------------------------------------------------------------


void AGame_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext, 0);
    }
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        UE_LOG(LogTemp, Display, TEXT("AGame_PlayerController::SetupInputComponent  is Success!"))
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AGame_PlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AGame_PlayerController::Look);
        EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AGame_PlayerController::OpenClosePauseMenu);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::SetupInputComponent  is FAIL!"));
    }

}


// Movement Player ------------------------------------------------------------------------------------------


void AGame_PlayerController::Move(const FInputActionValue& Value)
{
    FVector2D MoveDirect = Value.Get<FVector2D>();
    APawn* PossessedPawn = Cast<APawn>(GetPawn());
    if (PossessedPawn)
    {
        PossessedPawn->AddMovementInput(PossessedPawn->GetActorRightVector(), MoveDirect.X);
        PossessedPawn->AddMovementInput(PossessedPawn->GetActorForwardVector(), MoveDirect.Y);
    }
    

}
void AGame_PlayerController::Look(const FInputActionValue& Value)
{
    FVector2D LookDirect = Value.Get<FVector2D>();


}

void AGame_PlayerController::OpenClosePauseMenu()
{
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
    }
}


bool AGame_PlayerController::HiddenPauseMenu()
{
    if (PauseMenu)
    {
        PauseMenu->RemoveFromParent();
        PauseMenu = nullptr;
        return true;
    }
    else 
    {
        UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::HiddenPauseMenu: attempt to close a missing widget"));
        return false;
    }
}
bool AGame_PlayerController::ShowPauseMenu()
{
    if (!PauseMenu)
    {
        if (UralJam_GameInstance)
        {
                PauseMenu = CreateWidget<UUserWidget>(this, UralJam_GameInstance ->GetClass_Widget_PauseMenu());
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::ShowPauseMenu: UralJam_GameInstance is invalid pointer "));
        }
    }
    if (PauseMenu)
    {
        PauseMenu->AddToViewport();
        return true;
    }
    else 
    {
        UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::ShowPauseMenu: couldn't create widget PauseMenu"));
        return false;
    }
}
