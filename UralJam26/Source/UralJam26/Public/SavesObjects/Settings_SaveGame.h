// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Settings_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class URALJAM26_API USettings_SaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY(SaveGame)
	float MasterVolume = 0.5f;
};
