// Fill out your copyright notice in the Description page of Project Settings.


#include "UralJam_GameInstance.h"

void  UUralJam_GameInstance::StartGame()
{
	UE_LOG(LogTemp, Error, TEXT("GameInstance->StartGame"));//UralGame_LogEvents

	if (UWorld* World = GetWorld())
	{
		UGameplayStatics::OpenLevel(World, LevelName);
	}
}
