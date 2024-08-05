#include "JWK/CountInformation.h"

#include "Components/BoxComponent.h"
#include "Components/TextRenderComponent.h"

ACountInformation::ACountInformation()
{
	PrimaryActorTick.bCanEverTick = true;

	UTextRenderComponent* TotalCountText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TotalCountText"));
	RootComponent = TotalCountText;

	TotalCountText->SetRelativeLocation(FVector(0.f, 0.f, 60.f));
	TotalCountText->SetText(FText::FromString("TotalCount: 0 / 10"));
	TotalCountText->SetRelativeScale3D(FVector(100.0f));

	// UTextRenderComponent* WaterCountText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("WaterCountText"));
	// WaterCountText->SetupAttachment(RootComponent);
	// WaterCountText->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	// WaterCountText->SetText(FText::FromString("Water Count: 0"));
	//
	// UTextRenderComponent* ScrapsCountText = CreateDefaultSubobject<UTextRenderComponent>(TEXT("ScrapsCountText"));
	// ScrapsCountText->SetupAttachment(RootComponent);
	// ScrapsCountText->SetRelativeLocation(FVector(0.f, 0.f, 80.f));
	// ScrapsCountText->SetText(FText::FromString("Scraps Count: 0"));
}

void ACountInformation::BeginPlay()
{
	Super::BeginPlay();
}

void ACountInformation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACountInformation::UpdateCounts(int newWaterCount, int newScrapsCount)
{
	// waterCount = newWaterCount;
	// scrapsCount = newScrapsCount;
	// totalCount = waterCount + scrapsCount;

	totalCount = newWaterCount + newScrapsCount;

	UTextRenderComponent* WaterCountText = FindComponentByClass<UTextRenderComponent>();
	UTextRenderComponent* ScrapsCountText = FindComponentByClass<UTextRenderComponent>();
	UTextRenderComponent* TotalCountText = FindComponentByClass<UTextRenderComponent>();

	// if (WaterCountText)
	// 	// WaterCountText->SetText(FText::FromString(FString::Printf(TEXT("Water Count: %d"), waterCount)));
	// 	WaterCountText->SetText(FText::FromString(FString::Printf(TEXT("Water Count: %d"), newWaterCount)));
	//
	// if (ScrapsCountText)
	// 	// ScrapsCountText->SetText(FText::FromString(FString::Printf(TEXT("Scraps Count: %d"), scrapsCount)));
	// 	ScrapsCountText->SetText(FText::FromString(FString::Printf(TEXT("Scraps Count: %d"), newScrapsCount)));

	if (TotalCountText)
		if (totalCount <= 10)
			TotalCountText->SetText(FText::FromString(FString::Printf(TEXT("Total Count : %d / 10"), totalCount)));
}
