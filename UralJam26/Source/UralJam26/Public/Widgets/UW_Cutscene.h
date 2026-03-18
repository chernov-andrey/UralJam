// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Cutscene.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FEndCutscene);

UCLASS(Abstract)
class URALJAM26_API UUW_Cutscene : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FEndCutscene OnEndCutsceneEvent;
};
