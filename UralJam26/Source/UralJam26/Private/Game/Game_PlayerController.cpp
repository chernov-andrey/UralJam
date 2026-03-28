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
#include "Game\Master_Character.h"
#include "Intrfaces/Managment_Missions.h"
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
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("AGame_PlayerController::BeginPlay: FAIL CAST GameInstance to UralJam_GameInstance!"));
    }
    MCharacter =Cast<AMaster_Character>( GetCharacter());
    check(MCharacter);
  
    SetControlRotation(Rotator);
    GetPawn()->SetActorRotation(Rotator);


    Super::BeginPlay();
}


// Management game mod  ------------------------------------------------------------------------------------------


void AGame_PlayerController::ReplaceCharacter()
{
    int index = UralJam_GameInstance->CurrentClassHero;
    check(UralJam_GameInstance && "AGame_PlayerController::ReplaceCharacter: UralJam_GameInstance - invalid");
    check(UralJam_GameInstance->ListClassHero.IsValidIndex(index)&& "AGame_PlayerController::ReplaceCharacter: index - invalid");
    TSubclassOf<AMaster_Character> NewClass = UralJam_GameInstance->ListClassHero[index];
  /*  if (MCharacter->IsA(NewClass))
    {
        return;
    }*/
    FVector Loc = MCharacter->GetActorLocation()+FVector(0,0,300);

    UnPossess();
    MCharacter->Destroy();
    MCharacter = Cast<AMaster_Character>(GetWorld()->SpawnActor<ACharacter>(NewClass, Loc,Rotator));
    check(MCharacter);
    MCharacter->SetActorRotation(Rotator);
    Possess(MCharacter);
}


void AGame_PlayerController::ActivationController()
{
    SetPause(false);
    SubsystemInput->AddMappingContext(MappingContext_Char_Hero_2, 3);
    SubsystemInput->AddMappingContext(MappingContext_Char_Hero_1, 3);
    SubsystemInput->AddMappingContext(MappingContext_Char, 3);
}

void AGame_PlayerController::DeactivationController()
{
    SetPause(true);
    SubsystemInput->RemoveMappingContext(MappingContext_Char);
    SubsystemInput->RemoveMappingContext(MappingContext_Char_Hero_1);
    SubsystemInput->RemoveMappingContext(MappingContext_Char_Hero_2);
}
// Setup Input Component------------------------------------------------------------------------------------------


void AGame_PlayerController::CreateNew_Mission()
{
    

}

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
      
        SubsystemInput->AddMappingContext(MappingContext_Menu, 2);
    }
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
    {
        UE_LOG(LogTemp, Display, TEXT("AGame_PlayerController::SetupInputComponent  is Success!"))
        EnhancedInputComponent->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AGame_PlayerController::Move);
        EnhancedInputComponent->BindAction(IA_Attack, ETriggerEvent::Completed, this, &AGame_PlayerController::Attacks);

        EnhancedInputComponent->BindAction(IA_BlockAttack, ETriggerEvent::Triggered, this, &AGame_PlayerController::BlockAttack);
        EnhancedInputComponent->BindAction(IA_BlockAttack, ETriggerEvent::Completed, this, &AGame_PlayerController::BlockAttack);
      
        EnhancedInputComponent->BindAction(IA_AltAttack, ETriggerEvent::Triggered, this, &AGame_PlayerController::AltAttack);
        EnhancedInputComponent->BindAction(IA_Jump, ETriggerEvent::Triggered, this, &AGame_PlayerController::Jump);
        EnhancedInputComponent->BindAction(IA_AltJump, ETriggerEvent::Triggered, this, &AGame_PlayerController::AltJump);

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
    FVector2D V2;
    V2.X = Value.Get<FVector2D>().X;
    V2.Y=  Value.Get<FVector2D>().Y;
    MCharacter->Move_Character(V2);
}
void AGame_PlayerController::Attacks(const FInputActionValue& Value)
{
   MCharacter->Attack_Character(Value.Get<bool>());
}
void AGame_PlayerController::BlockAttack(const FInputActionValue& Value)
{
    MCharacter->Block_Character(Value.Get<bool>());
}

void AGame_PlayerController::AltAttack(const FInputActionValue& Value)
{
    MCharacter->AltAttack_Character(Value.Get<bool>());
}

void AGame_PlayerController::Jump(const FInputActionValue& Value)
{
    MCharacter->Jump_Character(Value.Get<bool>());
}

void AGame_PlayerController::AltJump(const FInputActionValue& Value)
{
    MCharacter->AltJump_Character(Value.Get<bool>());
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

//============================================================================================================================================
//                                             INTERFACES
//============================================================================================================================================

//--------------------------------------------- Management_Missions --------------------------------------


void AGame_PlayerController::CreateNewMission_Implementation(EMissionID ID)
{
    
    IManagment_Missions* Interface = Cast<IManagment_Missions>(MCharacter);
    if (Interface)
    {
        Interface->Execute_CreateNewMission(MCharacter, ID);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("UUralJam_GameInstance::CreateNewMission: PlayerController hasnt interface  -IManagment_Missions "));
    }
   
}
void AGame_PlayerController::CreateQuest_GoTo_Implementation(EMissionID ID, AEvent_Initiator_atMap* InitiatorActor)
{

    IManagment_Missions* Interface = Cast<IManagment_Missions>(MCharacter);
    if (Interface)
    {
        Interface->Execute_CreateQuest_GoTo(MCharacter, ID, InitiatorActor);

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AGame_PlayerController::CreateQuest_GoTo_Implementation: PlayerController hasnt interface  -IManagment_Missions "));
    }
}

void AGame_PlayerController::CreateQuest_KillAll_Implementation(EMissionID ID, int CountLiveEnemy)
{
    IManagment_Missions* Interface = Cast<IManagment_Missions>(MCharacter);
    if (Interface)
    {
        Interface->Execute_CreateQuest_KillAll(MCharacter, ID, CountLiveEnemy);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AGame_PlayerController::CreateQuest_GoTo_Implementation: PlayerController hasnt interface  -IManagment_Missions "));
    }

}

void AGame_PlayerController::UpdateQuest_KillAll_Implementation(EMissionID ID, int CountLiveEnemy)
{
    IManagment_Missions* Interface = Cast<IManagment_Missions>(MCharacter);
    if (Interface)
    {
        Interface->Execute_UpdateQuest_KillAll(MCharacter, ID, CountLiveEnemy);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AGame_PlayerController::UpdateQuest_KillAll_Implementation: PlayerController hasnt interface  -IManagment_Missions "));
    }

}
