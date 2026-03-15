// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "UralJam_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class URALJAM26_API UUralJam_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UPROPERTY(EditAnywhere, Category = "Game")
	FName LevelName = TEXT("MainLevel");
};
