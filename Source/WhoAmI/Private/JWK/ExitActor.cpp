#include "JWK/ExitActor.h"

#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

AExitActor::AExitActor()
{
	PrimaryActorTick.bCanEverTick = true;

	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);
	sphereComp->InitSphereRadius(50.0f);
	sphereComp->OnComponentBeginOverlap.AddDynamic(this, &AExitActor::OnOverlapBegin);
	
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));

	if(tempMesh.Succeeded())
		meshComp->SetStaticMesh(tempMesh.Object);

	meshComp->SetVisibility(true);
	meshComp->SetRelativeLocation(FVector(0.0f));
	meshComp->SetupAttachment(sphereComp);
	

	// 설사 사운드
	static ConstructorHelpers::FObjectFinder<USoundBase> FirstSound(TEXT("/Script/Engine.SoundCue'/Game/JWK/Sound/Poo/Water_Poo_Cue.Water_Poo_Cue'"));
	if (FirstSound.Succeeded())
		FirstEndingSound = FirstSound.Object;

	// 쾌변 사운드
	static ConstructorHelpers::FObjectFinder<USoundBase> ThirdSound(TEXT("/Script/Engine.SoundCue'/Game/JWK/Sound/Poo/Good_Poo_Cue.Good_Poo_Cue'"));
	if (ThirdSound.Succeeded())
		ThirdEndingSound = ThirdSound.Object;

	// 변기 물 사운드
	static ConstructorHelpers::FObjectFinder<USoundBase> FlushSound(TEXT("/Script/Engine.SoundCue'/Game/JWK/Sound/Poo/toilet_Sound_Cue.toilet_Sound_Cue'"));
	if (FlushSound.Succeeded())
		ToiletFlushSound = FlushSound.Object;
}

void AExitActor::BeginPlay()
{
	Super::BeginPlay();

	if (sphereComp && meshComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("sphereComp And meshComp Is NoCollision!!!!"));
		
		sphereComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		meshComp->SetVisibility(false);
	}

	OnCheckClearChanged.AddDynamic(this, &AExitActor::HandleCheckClearChanged);
}

void AExitActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AExitActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		UE_LOG(LogTemp, Warning, TEXT("Game Clear!!!! Game Clear!!!! Game Clear!!!! Game Clear!!!! Game Clear!!!! Game Clear!!!! "));

		CheckEnding();
	}
}

// 엔딩 체크 함수
void AExitActor::CheckEnding()
{
	if (bFirstEnding)		// 설사
		FirstEnding();	

	if (bSecondEnding)		// 변비
		SecondEnding();

	if (bThirdEnding)		// 쾌변
		ThirdEnding();

	FTimerHandle toiletTimer;
	float toiletTime = 5;
	
	// 딜레이 4 초
	GetWorld()->GetTimerManager().SetTimer(toiletTimer, FTimerDelegate::CreateLambda([ & ] ()
		{
			// 실행할 내용
			UGameplayStatics::PlaySoundAtLocation(this, ToiletFlushSound,GetActorLocation());
			
			// TimerHandle 초기화
			GetWorld()->GetTimerManager().ClearTimer(toiletTimer);
		}), toiletTime, false);
}

// 첫 번째 엔딩 : 설사
void AExitActor::FirstEnding()
{
	UE_LOG(LogTemp, Warning, TEXT("FirstEnding11111111111FirstEnding11111111111FirstEnding11111111111"));
	UGameplayStatics::PlaySoundAtLocation(this, FirstEndingSound, GetActorLocation());
}

// 두 번째 엔딩 : 변비
void AExitActor::SecondEnding()
{
	UE_LOG(LogTemp, Warning, TEXT("SecondEnding22222222222SecondEnding22222222222SecondEnding22222222222"));
}

// 세 번째 엔딩 : 쾌변
void AExitActor::ThirdEnding()
{
	UE_LOG(LogTemp, Warning, TEXT("ThirdEnding33333333333ThirdEnding33333333333ThirdEnding33333333333"));
	UGameplayStatics::PlaySoundAtLocation(this, ThirdEndingSound, GetActorLocation());
}

void AExitActor::SetCheckClear(bool bNewCheckClear)
{
	if (bCheckClear != bNewCheckClear)
	{
		bCheckClear = bNewCheckClear;
		OnCheckClearChanged.Broadcast();
	}
}

void AExitActor::HandleCheckClearChanged()
{
	if (bCheckClear)
	{
		UE_LOG(LogTemp, Warning, TEXT("bCheckClear Is True!!!"))
		sphereComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		meshComp->SetVisibility(true);
		meshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}