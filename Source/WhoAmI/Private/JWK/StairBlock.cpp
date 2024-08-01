#include "JWK/StairBlock.h"
#include "Components/BoxComponent.h"

AStairBlock::AStairBlock()
{
	PrimaryActorTick.bCanEverTick = true;

	FVector Positions[4] = {
		FVector(0.f, 0.f, 0.f),
		FVector(200.f, 0.f, 0.f),
		FVector(400.f, 0.f, 0.f),
		FVector(600.f, 0.f, 0.f)
	};

	for (int i = 0; i < 4; i++)
	{
		FString boxCompName = FString::Printf(TEXT("boxComp_%d"), i + 1);
		UBoxComponent* newBoxComp = CreateDefaultSubobject<UBoxComponent>(*boxCompName);

		if (newBoxComp)
		{
			boxComponents.Add(newBoxComp);

			if (RootComponent == nullptr)
				RootComponent = newBoxComp;

			else
				newBoxComp->SetupAttachment(RootComponent);

			newBoxComp->SetRelativeLocation(Positions[i]);
			newBoxComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
	}
}

void AStairBlock::BeginPlay()
{
	Super::BeginPlay();
}

void AStairBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStairBlock::OpenBlock()
{
	if (blockIndex < boxComponents.Num())
	{
		UBoxComponent* nextBlock = boxComponents[blockIndex];

		if (nextBlock)
		{
			nextBlock->SetCollisionEnabled(ECollisionEnabled::NoCollision);

			blockIndex++;
		}
	}
}
