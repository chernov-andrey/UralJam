// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu_PlayerController.h"

void AMenu_PlayerController::BeginPlay()
{
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}