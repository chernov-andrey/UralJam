// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors\A_Initiator_Cutscene.h"
#include "Components/SphereComponent.h"
#include "Game\UralJam_GameInstance.h"
#include "Game\Game_PlayerController.h"
#include "GameFramework\Character.h"
#include "Components\BillboardComponent.h"
#include "Kismet\GameplayStatics.h"

// Sets default values
AA_Initiator_Cutscene::AA_Initiator_Cutscene()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent",false);
	check(SphereComponent);
	
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>("BillboardComponent", false);
	check(BillboardComponent);
	BillboardComponent->SetupAttachment(SphereComponent); 
}


// Called when the game starts or when spawned
void AA_Initiator_Cutscene::BeginPlay()
{
	GameInstance = Cast<UUralJam_GameInstance>(GetGameInstance());
	check(GameInstance != nullptr);
	SphereComponent->OnComponentBeginOverlap.AddDynamic(this,&AA_Initiator_Cutscene::OnTriggered);
	Super::BeginPlay();
	
}

// Called every frame
void AA_Initiator_Cutscene::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AA_Initiator_Cutscene::OnTriggered(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ACharacter* PlayerCharacte = GameInstance->PlayerController->GetCharacter();
	if (PlayerCharacte == Cast<ACharacter>(OtherActor))
	{
		GameInstance->LaunchCutscene(WidgetType_Cutscene);
		this->Destroy();
	}
}

