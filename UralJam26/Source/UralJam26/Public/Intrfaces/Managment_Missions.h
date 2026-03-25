// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Managment_Missions.generated.h"

UINTERFACE(MinimalAPI)
class UManagment_Missions : public UInterface
{
	GENERATED_BODY()

public:

	
};
class URALJAM26_API IManagment_Missions
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Managment missions" )
	void CreateNewMission(const FString& Text) ;
	
};
