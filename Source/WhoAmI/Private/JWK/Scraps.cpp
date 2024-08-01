#include "JWK/Scraps.h"

#include "JWK/Collection_Component.h"
#include "JWK/Stairs.h"
#include "Kismet/GameplayStatics.h"

AScraps::AScraps()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));

	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AScraps::OnOverlapBegin);

	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/LevelPrototyping/Meshes/SM_ChamferCube.SM_ChamferCube'"));
	
	if (tempMesh.Succeeded())
		meshComp->SetStaticMesh(tempMesh.Object);
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
}

void AScraps::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AScraps::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Scraps Overlap Scraps Overlap Scraps Overlap Scraps Overlap Scraps Overlap Scraps Overlap "));

		boxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

		meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		meshComp->SetVisibility(false);
		
		if(stair)
			stair->CheckScrapsOverlap();

		if(nullptr == stair)
			UE_LOG(LogTemp, Warning, TEXT("scraps is Null!!"));
	}
}

