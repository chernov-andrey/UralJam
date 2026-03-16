// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_PlayerController.h"

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
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::SetupInputComponen  is Susse!"))
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AGame_PlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AGame_PlayerController::Look);
        EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AGame_PlayerController::PauseFlipFlop);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::SetupInputComponen  is FAIL!"));
    }

}

void AGame_PlayerController::PauseFlipFlop(const FInputActionValue& Value)
{
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
