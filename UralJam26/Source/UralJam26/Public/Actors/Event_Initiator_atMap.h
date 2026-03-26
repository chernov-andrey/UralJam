// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Event_Initiator_atMap.generated.h"

class USphereComponent;
class UBillboardComponent;
class UUralJam_GameInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTriggerCharacter);

UCLASS()
class URALJAM26_API AEvent_Initiator_atMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UPROPERTY(BlueprintCallable,BlueprintAssignable)
	FTriggerCharacter OnTriggerCharacterEvent;
	
	AEvent_Initiator_atMap();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( BlueprintReadOnly)
	UUralJam_GameInstance* GameInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr< UBillboardComponent> BillboardComponent;

	UPROPERTY(EditAnywhere)
	TObjectPtr< USphereComponent> SphereComponent;

	UFUNCTION()
	void OnTriggered(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
public:
	UFUNCTION(BlueprintImplementableEvent)
	void OnTrigger_Character();

	UFUNCTION(BlueprintImplementableEvent)
	void OnActivate();
	
	UFUNCTION(BlueprintCallable)
	void Activate();

};
