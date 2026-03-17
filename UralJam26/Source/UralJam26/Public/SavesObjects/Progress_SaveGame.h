// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Progress_SaveGame.generated.h"

/**
 * 
 */
UCLASS()
class URALJAM26_API UProgress_SaveGame : public USaveGame
{
	GENERATED_BODY()
public:
	bool bIsNewGame = true;
};
