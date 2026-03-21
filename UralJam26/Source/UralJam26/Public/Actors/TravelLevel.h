// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TravelLevel.generated.h"

class SphereComponent;
class UBillboardComponent;
class UUralJam_GameInstance;

UCLASS()
class URALJAM26_API ATravelLevel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATravelLevel();


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

	UPROPERTY(EditAnywhere)
	TObjectPtr< USphereComponent> SphereComponent;

	UFUNCTION()
	void OnTriggered(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);
};
