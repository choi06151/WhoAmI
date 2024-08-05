// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/GrinderActor.h"
#include "SEB/SEB_Player.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SEB/GaugeActor.h"

// Sets default values
AGrinderActor::AGrinderActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrinderComp = CreateDefaultSubobject<UBoxComponent>(TEXT("GrinderComp"));
	this->SetRootComponent(GrinderComp);
}

// Called when the game starts or when spawned
void AGrinderActor::BeginPlay()
{
	Super::BeginPlay();
	GrinderComp->OnComponentBeginOverlap.AddDynamic(this, &AGrinderActor::OnMyCompBeginOverlap);

	TSubclassOf<AActor> ActorClass = AGaugeActor::StaticClass();
	Gauge  = UGameplayStatics::GetActorOfClass(GetWorld(), ActorClass);
	GaugeInstance = Cast<AGaugeActor>(Gauge);

	
	
	
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Gauge"), GaugeBarActors );
}

void AGrinderActor::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ( OtherActor->IsA<ASEB_Player>() )
	{
		isCheck = true;
		UE_LOG(LogTemp, Error, TEXT("그라인더 앞에 있다."));
		ASEB_Player* player = Cast<ASEB_Player>(OtherActor); 
		//player->isPutDown = true;
		
		
	}
}

void AGrinderActor::OnMyCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ( OtherActor->IsA<ASEB_Player>() )
	{
		isCheck = false;
		UE_LOG(LogTemp, Error, TEXT("그라인더 앞에 있다."));
		
		
		
	}
}

// Called every frame
void AGrinderActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGrinderActor::IncrementGauge()
{
	UE_LOG(LogTemp, Error, TEXT("증가"));
	FString GaugeText = GaugeInstance->GaugeText->Text.ToString();
	int32 GaugeValue = FCString::Atoi(*GaugeText);
	GaugeValue++;
	GaugeInstance->GaugeText->SetText(FText::FromString(FString::FromInt(GaugeValue)));

	if (GaugeValue-1 <= 19 && GaugeBarActors[GaugeValue-1])
	{
		UStaticMeshComponent* MeshComponent = GaugeBarActors[GaugeValue-1]->FindComponentByClass<UStaticMeshComponent>();
		MeshComponent->SetMaterial(0, GaugeBarMaterial);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("오류나써염"));
	}
}
