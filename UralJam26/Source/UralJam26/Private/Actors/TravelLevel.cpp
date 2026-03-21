// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors/TravelLevel.h"
#include "Components\BillboardComponent.h"
#include "Components\SphereComponent.h"
#include "Game\UralJam_GameInstance.h"
#include "Game\Game_PlayerController.h"

// Sets default values
ATravelLevel::ATravelLevel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent", false);
	check(SphereComponent);

	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("BillboardComponent", false);
	check(BillboardComponent);
	BillboardComponent->SetupAttachment(SphereComponent);
}

// Called when the game starts or when spawned
void ATravelLevel::BeginPlay()
{
	GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	check(GameInstance != nullptr);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &ATravelLevel::OnTriggered);
	Super::BeginPlay();
	
}

// Called every frame
void ATravelLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATravelLevel::OnTriggered(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{
	//GameInstance->
}

