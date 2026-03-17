// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\Game_PlayerController.h"

void AGame_PlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;

}

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
        EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AGame_PlayerController::OpenCloseMenu);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::SetupInputComponent  is FAIL!"));
    }

}

void AGame_PlayerController::OpenCloseMenu()
{
    if (IsPaused())
    {
        UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::PauseFlipFlop : Pause = false"));
        SetPause(false);
        if (HiddenMainMenu())
        {
            SetInputMode(FInputModeGameOnly());
            bShowMouseCursor = false;
        }
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::PauseFlipFlop : Pause = true"));
        SetPause(true);
        if (ShowMainMenu())
        {
            SetInputMode(FInputModeGameAndUI());
            bShowMouseCursor = true;
        }
    }
}
bool AGame_PlayerController::HiddenMainMenu()
{
    if (MainMenu)
    {
        MainMenu->RemoveFromParent();
        MainMenu = nullptr;
        return true;
    }
    else 
    {
        UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::HiddenMainMenu: attempt to close a missing widget"));
        return false;
    }
}
bool AGame_PlayerController::ShowMainMenu()
{
    if (!MainMenu)
    {
        if (UUralJam_GameInstance* GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance()))
        {
            if (TSubclassOf<UUserWidget> ClassWidget = GameInstance->GetClass_Widget_PauseMenu())
            {
                MainMenu = CreateWidget<UUserWidget>(this, ClassWidget);
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::ShowMainMenu: UUralJam_GameInstance - Widget_MainMenu Not a definition"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::ShowMainMenu: another class was expected GameInstance"));
        }
    }
    if (MainMenu)
    {
        MainMenu->AddToViewport();
        return true;
    }
    else 
    {
        UE_LOG(LogTemp, Display, TEXT(" AGame_PlayerController::ShowMainMenu: couldn't create widget MainMenu"));
        return false;
    }
}
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
