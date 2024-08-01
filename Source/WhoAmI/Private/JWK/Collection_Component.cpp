#include "JWK/Collection_Component.h"

UCollection_Component::UCollection_Component()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCollection_Component::BeginPlay()
{
	Super::BeginPlay();
	
	waterCount = 0;
	scrapsCount = 0;
}

void UCollection_Component::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UCollection_Component::CheckTotalCount()
{
	if (waterCount > 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("Too Many Water!! Too Many Water!! Too Many Water!! Too Many Water!! Too Many Water!!"));
	}

	if (scrapsCount > 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("Too Many Scraps!! Too Many Scraps!! Too Many Scraps!! Too Many Scraps!! Too Many Scraps!!"));
	}
	
	if (waterCount == 5 || scrapsCount == 5)
	{
		UE_LOG(LogTemp, Warning, TEXT("Very Good!! Very Good!! Very Good!! Very Good!! Very Good!! Very Good!!"));
	}
}

void UCollection_Component::IncreaseWater()
{
	waterCount++;
	UE_LOG(LogTemp, Warning, TEXT("Water Count : %d"), waterCount);
}

void UCollection_Component::IncreaseScraps()
{
	scrapsCount++;
	UE_LOG(LogTemp, Warning, TEXT("Scraps Count : %d"), scrapsCount);
}
