// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structures/CharacterStats.h"
#include "Intrfaces/Managment_Missions.h"
#include "Data/PDA_Character_Events.h"
#include "Master_Character.generated.h"

class AEvent_Initiator_atMap;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FCompleteQuest, EMissionID, ID);

UCLASS(Abstract)
class URALJAM26_API AMaster_Character : public ACharacter, public IManagment_Missions
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable,BlueprintCallable)
	FCompleteQuest OnCompleteQuestEvent;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<UPDA_Character_Events> DA_events;

	// Sets default values for this character's properties
	AMaster_Character();
	
	UFUNCTION(BlueprintImplementableEvent)
	void Move_Character(FVector2D InputValue);

	UFUNCTION(BlueprintImplementableEvent)
	void Jump_Character(bool InputValue);

	UFUNCTION(BlueprintImplementableEvent)
	void AltJump_Character(bool InputValue);

	UFUNCTION(BlueprintImplementableEvent)
	void Attack_Character(bool InputValue);

	UFUNCTION(BlueprintImplementableEvent)
	void AltAttack_Character(bool InputValue);

	UFUNCTION(BlueprintImplementableEvent)
	void Block_Character(bool InputValue);

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Character Stats")
	FCharacterStats Stats;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//============================================================================================================================================
//                                             INTERFACES
//============================================================================================================================================

//--------------------------------------------- Management_Missions --------------------------------------
public:
	virtual void CreateNewMission_Implementation(EMissionID ID) override;
	virtual void CreateQuest_GoTo_Implementation(EMissionID ID, AEvent_Initiator_atMap* InitiatorActor) override;

};
