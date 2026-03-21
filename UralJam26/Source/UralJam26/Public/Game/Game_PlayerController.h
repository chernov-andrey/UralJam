// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Game_PlayerController.generated.h"

class UUralJam_GameInstance;
class UInputAction;
class UInputMappingContext;
class UUserWidget;
class ACharacter;
class AMaster_Character;
class UEnhancedInputLocalPlayerSubsystem;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSkipCutscene, bool, skipAll);
UCLASS()
class URALJAM26_API AGame_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	FOnSkipCutscene OnSkipCutsceneEvent;

private:
	UPROPERTY()
	TObjectPtr<UEnhancedInputLocalPlayerSubsystem> SubsystemInput;
public:
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Move;
	
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Pause;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Attack;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_BlockAttack;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_AltAttack;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Jump;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_AltJump;


	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Skip_All;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputAction> IA_Skip_One;


	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext_Char;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext_Char_Hero_1;

	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext_Char_Hero_2;
	
	UPROPERTY(EditAnywhere, Category = "Settings Controller Game_PlayerController | Input Settings")
	TObjectPtr<UInputMappingContext> MappingContext_Menu;

	void SkipAll();
	void SkipOne();


private:
	virtual void SetupInputComponent() override;
	virtual  void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UUralJam_GameInstance>	UralJam_GameInstance;

	AMaster_Character* Character;
public:

	UFUNCTION()
	bool TeleportToTargetPoint(FName Tag_TargetPoint);

	// Management game mod ------------------------------------------------------------------------------------

public:
	UFUNCTION()
	void ActivationController();
	UFUNCTION()
	void DeactivationController();
private:
	void OpenClosePauseMenu();


	// Management move ------------------------------------------------------------------------------------
	

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void Attack(const FInputActionValue& Value);

	UFUNCTION()
	void BlockAttack(const FInputActionValue& Value);
	
	UFUNCTION()
	void AltAttack(const FInputActionValue& Value);
	
	UFUNCTION()
	void Jump(const FInputActionValue& Value);
	
	UFUNCTION()
	void AltJump(const FInputActionValue& Value);

};
