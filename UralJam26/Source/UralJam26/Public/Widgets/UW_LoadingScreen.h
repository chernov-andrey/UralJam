// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_LoadingScreen.generated.h"

/**
 * 
 */
UCLASS()
class URALJAM26_API UUW_LoadingScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent)
	void Deferred_RemoveFromParent();
};
