#include "JWK/Scraps.h"

#include "JWK/Collection_Component.h"
#include "JWK/Stairs.h"
#include "Kismet/GameplayStatics.h"

AScraps::AScraps()
{
	PrimaryActorTick.bCanEverTick = true;

	FVector Positions[5] = {
		FVector(15.0f, 0.0f, 0.0f),
		FVector(-15.0f, 0.0f, 0.0f),
		FVector(0.0f, 15.0f, 0.0f),
		FVector(0.0f, -15.0f, 0.0f),
		FVector(0.0f, 0.0f, 20.0f)
	};

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	RootComponent = boxComp;

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	for (int i = 0; i < 5; i++)
	{
		FString meshCompName = FString::Printf(TEXT("meshComp%d"), i + 1);
		UStaticMeshComponent* newMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(*meshCompName);
		newMeshComp->SetupAttachment(boxComp);
		newMeshComp->SetRelativeLocation(Positions[i]);
        
		if(tempMesh.Succeeded())
			newMeshComp->SetStaticMesh(tempMesh.Object);

		newMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		meshComponents.Add(newMeshComp);
	}


	// meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	// meshComp->SetupAttachment(boxComp);
	//
	// ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	//
	// if (tempMesh.Succeeded())
	// 	meshComp->SetStaticMesh(tempMesh.Object);
}

void AScraps::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStairs::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
		stair = Cast<AStairs>(FoundActors[0]);

	if (!stair)
		UE_LOG(LogTemp, Warning, TEXT("stair is Null!!"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AScraps::OnOverlapBegin);
}

void AScraps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AScraps::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		// meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		for (UStaticMeshComponent* meshComp : meshComponents)
			meshComp->SetVisibility(false);
		
		UGameplayStatics::PlaySoundAtLocation(this, scrapSound, GetActorLocation());

		if (stair)
			stair->CheckScrapsOverlap();

		if (nullptr == stair)
			UE_LOG(LogTemp, Warning, TEXT("scraps is Null!!"));
	}
}
