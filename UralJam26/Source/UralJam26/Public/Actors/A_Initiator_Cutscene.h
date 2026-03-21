// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_Initiator_Cutscene.generated.h"

class UUW_Cutscene;
class USphereComponent;
class UUralJam_GameInstance;
class UBillboardComponent;

	UCLASS()
class URALJAM26_API AA_Initiator_Cutscene : public AActor
{
	GENERATED_BODY()public:
	UPROPERTY(EditAnywhere)
	TObjectPtr< USphereComponent> SphereComponent;

public:	
	// Sets default values for this actor's properties
	AA_Initiator_Cutscene();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Cutscene")
	TSubclassOf<UUW_Cutscene> WidgetType_Cutscene;
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UUralJam_GameInstance* GameInstance;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr< UBillboardComponent> BillboardComponent;

	UFUNCTION()
	void OnTriggered(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
};
