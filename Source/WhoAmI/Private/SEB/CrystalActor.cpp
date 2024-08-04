// Fill out your copyright notice in the Description page of Project Settings.

#include "SEB/CrystalActor.h"

#include "Kismet/GameplayStatics.h"
#include "SEB/GaugeActor.h"
#include "SEB/SEB_Player.h"
#include "SEB/TextActor.h"


// Sets default values
ACrystalActor::ACrystalActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CrystalComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CrystalComp"));
	this->SetRootComponent(CrystalComp);

	CrystalComp->SetBoxExtent(FVector(100));
	Crystal = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Crystal"));
	Crystal->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACrystalActor::BeginPlay()
{
	Super::BeginPlay();
	CrystalComp->OnComponentBeginOverlap.AddDynamic(this, &ACrystalActor::OnMyCompBeginOverlap);


	TSubclassOf<AActor> ActorClass = ATextActor::StaticClass();
	Text  = UGameplayStatics::GetActorOfClass(GetWorld(), ActorClass);
	TextActorInstance = Cast<ATextActor>(Text);
}

// Called every frame
void ACrystalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystalActor::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ( OtherActor->IsA<ASEB_Player>() )
	{
		ASEB_Player* player = Cast<ASEB_Player>(OtherActor);
		player->isHold = true;

		FString InfoText = TEXT("수집한 광석을 \n 그라인더에 올려주세요.");
		TextActorInstance->InfoText->SetText(FText::FromString(InfoText));

		//DestroyCrystal();
		
	}
}

void ACrystalActor::DestroyCrystal()
{
	
	
	UE_LOG(LogTemp, Error, TEXT("ACrystalActor::DestroyCrystal()"));
	
}



