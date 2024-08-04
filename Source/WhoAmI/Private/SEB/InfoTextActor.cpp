// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/InfoTextActor.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AInfoTextActor::AInfoTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InfoText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("InfoText"));

	RootComponent = InfoText;

	InfoText->SetTextMaterial(textMtr);
	InfoText->SetFont(textFont);
}

// Called when the game starts or when spawned
void AInfoTextActor::BeginPlay()
{
	Super::BeginPlay();
	InfoText->SetText(FText::FromString("A버튼을 눌러 \n 곡괭이를 획득하세요."));
}

// Called every frame
void AInfoTextActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInfoTextActor::ClickAButton()
{
	InfoText->SetText(FText::FromString(TEXT("aaaaaaaaaaaa")));
}

