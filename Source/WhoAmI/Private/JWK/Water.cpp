#include "JWK/Water.h"

#include "JWK/Collection_Component.h"
#include "JWK/Stairs.h"
#include "Kismet/GameplayStatics.h"

AWater::AWater()
{
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	sphereComp->InitSphereRadius(50.0f);
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AWater::OnOverlapBegin);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(sphereComp);

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if (tempMesh.Succeeded())
		meshComp->SetStaticMesh(tempMesh.Object);
}

void AWater::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStairs::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
		stair = Cast<AStairs>(FoundActors[0]);

	if (!stair)
		UE_LOG(LogTemp, Warning, TEXT("stair is Null!!"));
}

void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWater::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Water Overlap Water Overlap Water Overlap Water Overlap Water Overlap Water Overlap"));

		sphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		meshComp->SetVisibility(false);
		meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		if(stair)
			stair->CheckWaterOverlap();

		if(nullptr == stair)
			UE_LOG(LogTemp, Warning, TEXT("stair is Null!!"));
	}
}
