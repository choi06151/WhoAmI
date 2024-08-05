// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/GaugeActor.h"

#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SEB/DoorActor.h"

// Sets default values
AGaugeActor::AGaugeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GaugeText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("GaugeText"));
	RootComponent = GaugeText;
	MaxGaugeText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("MaxGaugeText"));
}

// Called when the game starts or when spawned
void AGaugeActor::BeginPlay()
{
	Super::BeginPlay();

	GaugeText->SetText(FText::FromString("0"));
	MaxGaugeText->SetText(FText::FromString("/ 20"));


	TSubclassOf<AActor> ActorClass = ADoorActor::StaticClass();
	Door  = UGameplayStatics::GetActorOfClass(GetWorld(), ActorClass);
	StartPosition = Door->GetActorLocation();
	TargetPosition =  FVector(-3410, -7230.0, 1780.0);
	bIsOpening = true;
}

// Called every frame
void AGaugeActor::Tick(float DeltaTime)
{ 
	Super::Tick(DeltaTime);

	//우선 tick에 넣어두는데 원래는 crystal이 깨질때마다 카운트를 하고 20이 되었을 때 이 함수를 호출하도록 하기.
	if(GaugeText->Text.ToString() == "20")  
	{
		OpenDoor(DeltaTime);
	}
	
}

void AGaugeActor::OpenDoor(float DeltaTime)
{
	if(Door && bIsOpening )
	{
		FVector CurrentPosition = Door->GetActorLocation();
		FVector Direction = (TargetPosition - StartPosition).GetSafeNormal();

		FVector NewPosition = CurrentPosition + Direction * DoorOpeningSpeed * DeltaTime;

		if (FVector::Dist(NewPosition, StartPosition) >= FVector::Dist(TargetPosition, StartPosition))
		{
			NewPosition = TargetPosition;
			bIsOpening = false;  
		}

		Door->SetActorLocation(NewPosition);
	}
}

