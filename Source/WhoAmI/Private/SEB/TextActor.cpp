// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/TextActor.h"

#include "Components/TextRenderComponent.h"

// Sets default values
ATextActor::ATextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InfoText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InfoText"));

	RootComponent = InfoText;
	InfoText->SetTextMaterial(textMtr);
	InfoText->SetFont(textFont);
}

// Called when the game starts or when spawned
void ATextActor::BeginPlay()
{
	Super::BeginPlay();
	FString Text = TEXT("A버튼을 눌러 \n 곡괭이를 획득하세요.");

	InfoText->SetText(FText::FromString(Text));
}

// Called every frame
void ATextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATextActor::ClickAButton()
 {
	if(InfoText)
	{
		FString Text = TEXT("곡괭이를 이용하여 \n 오른쪽의 광석을 수집하세요.");

		InfoText->SetText(FText::FromString(Text));
	}
	
	else
	{
		UE_LOG(LogTemp, Error, TEXT("읎다,.."));
	}
 }

