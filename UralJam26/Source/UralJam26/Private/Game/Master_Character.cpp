// Fill out your copyright notice in the Description page of Project Settings.


#include "Game\Master_Character.h"

#include "Intrfaces/Damageable_Interface.h"

// Sets default values
AMaster_Character::AMaster_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMaster_Character::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMaster_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMaster_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
void AMaster_Character::CreateNewMission_Implementation(EMissionID ID)
{
	UE_LOG(LogTemp, Warning, TEXT(" AMaster_Character::CreateNewMission_Implementation: not override"));
}


void AMaster_Character::CreateQuest_GoTo_Implementation(EMissionID ID, AEvent_Initiator_atMap* InitiatorActor)
{
	UE_LOG(LogTemp, Warning, TEXT(" AMaster_Character::CreateQuest_GoTo_Implementation: not override"));
}

void AMaster_Character::CreateQuest_KillAll_Implementation(EMissionID ID, int CountLiveEnemy)
{
	UE_LOG(LogTemp, Warning, TEXT(" AMaster_Character::CreateQuest_KillAll_Implementation: not override"));
}

void AMaster_Character::UpdateQuest_KillAll_Implementation(EMissionID ID, int CountLiveEnemy)
{
	UE_LOG(LogTemp, Warning, TEXT(" AMaster_Character::CreateQuest_KillAll_Implementation: not override"));
}

