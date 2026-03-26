// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PDA_Character_Events.generated.h"

class UUW_Cutscene;

UENUM(BlueprintType)
enum class ECutsceneID : uint8
{
	Lvl_1_Cut_1,
	Lvl_1_Cut_2,
	Lvl_1_Cut_3,
	Lvl_2_Cut_1,
	Lvl_2_Cut_2,
	Lvl_2_Cut_3,
};

UENUM(BlueprintType)
enum class EMissionID : uint8
{
	Mission_1,
	Mission_2,
	Mission_3,
	Mission_4,
	Mission_5,
	Mission_6
};

UCLASS()
class URALJAM26_API UPDA_Character_Events : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TMap<ECutsceneID, TSubclassOf<UUW_Cutscene>> ListCutscenes;


};
