// Fill out your copyright notice in the Description page of Project Settings.

#include "SEB/CrystalActor.h"

#include "Kismet/GameplayStatics.h"
#include "SEB/GaugeActor.h"
#include "SEB/SEB_Player.h"


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

	
}

// Called every frame
void ACrystalActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACrystalActor::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ( OtherActor->IsA<ASEB_Player>() ) // 플레이어랑 크리스탈이랑 충돌하면
	{
		//이거 나중에 플레이어에서 가져오기
		ASEB_Player* player = Cast<ASEB_Player>(OtherActor);
		player->isHold = true; // 크리스탈을 잡고있다는 것을 표시
		UE_LOG(LogTemp, Error, TEXT("크리스탈을 집었다!"));
		//IncrementGauge();
		//DestroyCrystal();
		
	}
}

void ACrystalActor::DestroyCrystal()
{
	
	
	UE_LOG(LogTemp, Error, TEXT("ACrystalActor::DestroyCrystal()"));
	
}



