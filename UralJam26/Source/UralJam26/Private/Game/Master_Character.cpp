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

