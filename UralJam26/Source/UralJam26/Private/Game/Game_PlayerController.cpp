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
            UralJam_GameInstance->SetPlayerController(this);

            UralJam_GameInstance->CreateMainMenu_Widget();
            UralJam_GameInstance->CreateSplashScreen_Widget();
         
            DisableInput(this);
            SetInputMode(FInputModeUIOnly());
            bShowMouseCursor = true;

            UralJam_GameInstance->OnGameStartedEvent.AddDynamic(this,&ThisClass::ActivationController);      
        }

    }
    else
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

void AGame_PlayerController::ActivationController()
{
    //Выбрать место

}

// Setup Input Component------------------------------------------------------------------------------------------


void AGame_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
        ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(MappingContext_Game, 1);
        Subsystem->AddMappingContext(MappingContext_Menu, 0);
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
    UralJam_GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
    if (UralJam_GameInstance)
    {
        UralJam_GameInstance->OpenClosePauseMenu();
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::BeginPlay: FAIL CAST GameInstance to UralJam_GameInstance!"));
    }
}


