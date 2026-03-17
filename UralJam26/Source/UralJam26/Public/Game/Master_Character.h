// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Structures/CharacterStats.h"
#include "Intrfaces/Damageable_Interface.h"
#include "Master_Character.generated.h"


UCLASS(Abstract)
class URALJAM26_API AMaster_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMaster_Character();
	

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Character Stats")
	FCharacterStats Stats;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
