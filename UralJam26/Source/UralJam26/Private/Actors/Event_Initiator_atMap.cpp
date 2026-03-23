// Fill out your copyright notice in the Description page of Project Settings.

#include "Actors\Event_Initiator_atMap.h"
#include "Components\BillboardComponent.h"
#include "Components\SphereComponent.h"
#include "Game\UralJam_GameInstance.h"
#include "Game\Game_PlayerController.h"

// Sets default values
AEvent_Initiator_atMap::AEvent_Initiator_atMap()
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
void AEvent_Initiator_atMap::BeginPlay()
{
	GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	check(GameInstance != nullptr);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEvent_Initiator_atMap::OnTriggered);
	Super::BeginPlay();
	
}

// Called every frame
void AEvent_Initiator_atMap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEvent_Initiator_atMap::OnTriggered(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult) 
{
	if (OtherActor == Cast<AActor>(GameInstance->PlayerController->GetCharacter()))
	{
		AEvent_Initiator_atMap::OnTrigger_Character();
	}
}

