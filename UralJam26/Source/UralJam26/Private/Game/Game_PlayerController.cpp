// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\Game_PlayerController.h"
#include "InputAction.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Engine\TargetPoint.h"
#include "GameFramework/Character.h"
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
         
            bShowMouseCursor = true;

            //UralJam_GameInstance->OnGameStartedEvent.AddDynamic(this,&ThisClass::ActivationController);      
        }

    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::BeginPlay: FAIL CAST GameInstance to UralJam_GameInstance!"));
    }
    Character = GetCharacter();
    check(Character);
   
   
    Super::BeginPlay();
}


// Management game mod  ------------------------------------------------------------------------------------------




bool AGame_PlayerController::TeleportToTargetPoint(FName Tag_TargetPoint)
{
    if (!Tag_TargetPoint.IsValid()) 
    {
        return false;
    }
    TArray<AActor*,FDefaultAllocator> allActors;
 
    UGameplayStatics::GetAllActorsOfClassWithTag(this, ATargetPoint::StaticClass(), Tag_TargetPoint, allActors);
    if (allActors.IsEmpty())
    {
        return false;
    }

    GetPawn()->SetActorLocationAndRotation(allActors[0]->GetActorLocation(), allActors[0]->GetActorRotation());
    return true;
}

void AGame_PlayerController::ActivationController()
{
    Character->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AGame_PlayerController::DeactivationController()
{
    Character->GetCharacterMovement()->DisableMovement();
}
// Setup Input Component------------------------------------------------------------------------------------------


void AGame_PlayerController::SkipAll()
{
    OnSkipCutsceneEvent.Broadcast(true);
}

void AGame_PlayerController::SkipOne()
{
    OnSkipCutsceneEvent.Broadcast(false);
}

void AGame_PlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    SubsystemInput = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    if (SubsystemInput)
    {
        SubsystemInput->AddMappingContext(MappingContext_Game, 0);
        SubsystemInput->AddMappingContext(MappingContext_Menu, 1);    
    }
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        UE_LOG(LogTemp, Display, TEXT("AGame_PlayerController::SetupInputComponent  is Success!"))
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AGame_PlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AGame_PlayerController::Look);
        EnhancedInputComponent->BindAction(IA_Pause, ETriggerEvent::Triggered, this, &AGame_PlayerController::OpenClosePauseMenu);
       
        EnhancedInputComponent->BindAction(IA_Skip_All, ETriggerEvent::Triggered, this, &AGame_PlayerController::SkipAll);
        EnhancedInputComponent->BindAction(IA_Skip_One, ETriggerEvent::Triggered, this, &AGame_PlayerController::SkipOne);
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


