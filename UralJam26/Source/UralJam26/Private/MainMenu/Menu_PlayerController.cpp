// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu\Menu_PlayerController.h"

void AMenu_PlayerController::BeginPlay()
{
	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;

}