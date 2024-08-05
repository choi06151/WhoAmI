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

	FloatAmplitude = 10.0f; // 진폭
	FloatFrequency = 2.0f; // 주기
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

	InitialLocation = GetActorLocation();
}

void AWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (FloatFrequency > 0)
	{
		// Sine 함수를 사용하여 물체의 위치를 주기적으로 변경
		float DeltaHeight = FloatAmplitude * FMath::Sin(FloatFrequency * GetWorld()->TimeSeconds);
		FVector NewLocation = InitialLocation;
		NewLocation.Z += DeltaHeight;

		SetActorLocation(NewLocation);
	}
}

void AWater::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		sphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		meshComp->SetVisibility(false);
		meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		UGameplayStatics::PlaySoundAtLocation(this, waterSound, GetActorLocation());
		
		if (stair)
			stair->CheckWaterOverlap();

		if (nullptr == stair)
			UE_LOG(LogTemp, Warning, TEXT("stair is Null!!"));
	}
}
