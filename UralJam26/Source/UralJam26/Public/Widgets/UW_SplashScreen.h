// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_SplashScreen.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCloseSplashScreen);

UCLASS()
class URALJAM26_API UUW_SplashScreen : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FCloseSplashScreen OnCloseSplashScreenEvent;
};
