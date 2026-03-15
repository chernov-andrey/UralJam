// Fill out your copyright notice in the Description page of Project Settings.


#include "UW_MainMenu.h"


void UUW_MainMenu::OnStartGameButtonClicked()
{

	if (UUralJam_GameInstance* UralJam_GameInstance = GetUralJam_GameInstance())
	{
		UralJam_GameInstance->StartGame();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("GameInstance_Main not found!"));
	}

}

void UUW_MainMenu::OnExitGameButtonClicked()
{

	if (APlayerController* PlayerController = GetOwningPlayer())
	{
		PlayerController->ConsoleCommand("quit");
	}
}

UUralJam_GameInstance* UUW_MainMenu::GetUralJam_GameInstance()
{
	UGameInstance* GameInstance = GetGameInstance();
	return Cast<UUralJam_GameInstance>(GameInstance);
}

void UUW_MainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGameButton)
	{
		StartGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnStartGameButtonClicked);
		ExitGameButton->OnClicked.AddDynamic(this, &UUW_MainMenu::OnExitGameButtonClicked);
	}
}

