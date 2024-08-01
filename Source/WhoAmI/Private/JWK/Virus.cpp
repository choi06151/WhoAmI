#include "JWK/Virus.h"

#include "Components/BoxComponent.h"

AVirus::AVirus()
{
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("boxComp"));
	boxComp->OnComponentBeginOverlap.AddDynamic(this, &AVirus::OnOverlapBegin);
	
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(boxComp);
}

void AVirus::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVirus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AVirus::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlap Begin: %s"), *OtherActor->GetName());
		// 여기서 오버랩이 발생했을 때의 행동을 정의
	}
}

