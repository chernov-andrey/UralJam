// Fill out your copyright notice in the Description page of Project Settings.


#include "Game_PlayerController.h"

void AGame_PlayerController::BeginPlay()
{
	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
