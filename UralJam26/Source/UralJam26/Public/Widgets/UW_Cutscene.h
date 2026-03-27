// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Cutscene.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FShownOpening);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEndCutscene, UUW_Cutscene*,CutscenePtr);

UCLASS(Abstract)
class URALJAM26_API UUW_Cutscene : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	ECutsceneID ID;


	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bCanBeSkip=false;
	
	UFUNCTION(BlueprintCallable)
	void SkipCutscene(bool SkipAll);
	
	UFUNCTION(BlueprintCallable)
	void EndCutscene();
	
	UFUNCTION(BlueprintImplementableEvent)
	 void SkipCutsceneFrame();
	
	 UPROPERTY(BlueprintAssignable)
	FEndCutscene OnEndCutsceneEvent;
	UPROPERTY(BlueprintCallable)
	FShownOpening OnShownOpeningEvent;
};
