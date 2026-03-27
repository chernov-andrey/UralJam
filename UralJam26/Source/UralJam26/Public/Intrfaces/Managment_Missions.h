// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Data/PDA_Character_Events.h"
#include "Actors\Event_Initiator_atMap.h"
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
	void CreateNewMission(EMissionID ID);
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Managment missions")
	void CreateQuest_GoTo(EMissionID ID, AEvent_Initiator_atMap* InitiatorActor);

};
