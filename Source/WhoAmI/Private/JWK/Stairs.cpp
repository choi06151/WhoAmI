#include "JWK/Stairs.h"

#include "JWK/CountInformation.h"
#include "JWK/ExitActor.h"
#include "JWK/StairBlock.h"
#include "Kismet/GameplayStatics.h"

AStairs::AStairs()
{
	PrimaryActorTick.bCanEverTick = true;

	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Crystal_cave/Meshes/Stairs/SM_stairs_01.SM_stairs_01'"));

	for (int i = 0; i < 5; i++) // n번 계단 meshComp 추가
	{
		////////////////////////////////////// 계단 //////////////////////////////////////
		FString meshCompName = FString::Printf(TEXT("meshComp_%d"), i + 1); // 1번 부터
		UStaticMeshComponent* newMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(*meshCompName);

		if (tempMesh.Succeeded())
			newMeshComp->SetStaticMesh(tempMesh.Object);

		meshComponents.Add(newMeshComp);

		newMeshComp->SetVisibility(true);
		newMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		/////////////////////////////////////////////////////////////////////////////////
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> tempCaveSound(TEXT("/Script/Engine.SoundWave'/Game/JWK/Sound/Cave_Sound.Cave_Sound'"));
	if (tempCaveSound.Succeeded())
		caveSound = tempCaveSound.Object;
}

void AStairs::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySound2D(this, caveSound, 0.3f);
	
	// 게임이 시작될 때 모든 메시를 비활성화
	for (UStaticMeshComponent* meshComp : meshComponents)
	{
		if (meshComp)
		{
			meshComp->SetVisibility(false);
			meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	// Stair Block Cast
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AStairBlock::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		stairBlock = Cast<AStairBlock>(FoundActors[0]);
		UE_LOG(LogTemp, Warning, TEXT("stair is not Null!!!!!!!!!!!!! stair is not Null!!!!!!!!!!!!! stair is not Null!!!!!!!!!!!!! stair is not Null!!!!!!!!!!!!!"));
	}

	if (!stairBlock)
		UE_LOG(LogTemp, Warning, TEXT("stair is Null!!"));


	// Exit Cast
	exitActor = Cast<AExitActor>(UGameplayStatics::GetActorOfClass(GetWorld(), AExitActor::StaticClass()));

	if (exitActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("ExitActor is not Null!!"));
		exitActor->OnCheckClearChanged.AddDynamic(this, &AStairs::CheckTotalCount);
	}

	if (!exitActor)
		UE_LOG(LogTemp, Warning, TEXT("exit is Null!!"));

	
	// CountInformation Cast
	TArray<AActor*> FoundActors2;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ACountInformation::StaticClass(), FoundActors2);

	if (FoundActors2.Num() > 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("CountInformation is not Null!!"));
		CountInformationActor = Cast<ACountInformation>(FoundActors2[0]);
	}

	if (!CountInformationActor)
		UE_LOG(LogTemp, Warning, TEXT("CountInformation is Null!!"));
}

void AStairs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AStairs::CheckWaterOverlap()
{
	waterCount++;
	UE_LOG(LogTemp, Warning, TEXT("waterCount : %d"), waterCount);

	CheckTotalCount();

	if (CountInformationActor)
		CountInformationActor->UpdateCounts(waterCount, scrapsCount);
}

void AStairs::CheckScrapsOverlap()
{
	scrapsCount++;
	UE_LOG(LogTemp, Warning, TEXT("scrapsCount : %d"), scrapsCount);

	CheckTotalCount();

	if (CountInformationActor)
		CountInformationActor->UpdateCounts(waterCount, scrapsCount);
}

void AStairs::CheckTotalCount()
{
	int totalCount = waterCount + scrapsCount;

	UE_LOG(LogTemp, Warning, TEXT("Total Count : %d"), totalCount);

	if (CountInformationActor)
		CountInformationActor->UpdateCounts(waterCount, scrapsCount);
	
	// 총 수집 개수가 2개, 4개, 6개, 8개, 10개 일 때 출구호 향하는 계단이 나타남
	if (totalCount % 2 == 0 && totalCount <= 10)
		ShowNextStair();

	// 계단이 나타나고 다음 계단이 나타나기 전에 플레이어가 떨어지는 걸 방지하기 위해 보이지않는 벽의 Collision을 관리함
	if (totalCount > 3 && totalCount % 2 == 0)
	{
		if (stairBlock)
			stairBlock->OpenBlock(); // 보이지 않는 벽의 Collision을 NoCollision으로

		else
			UE_LOG(LogTemp, Warning, TEXT("stairBlock is null!!! stairBlock is null!!! stairBlock is null!!! stairBlock is null!!!"));
	}

	// 엔딩 조건 체크
	if (totalCount == 10)
	{
		if (waterCount >= 7) // 많은 수분, 적은 찌꺼기
		{
			UE_LOG(LogTemp, Warning, TEXT("Unbalanced. Water is more than Scraps"));

			// 1. 설사 엔딩
			if (exitActor)
			{
				exitActor->bFirstEnding = true;
				exitActor->SetCheckClear(true);
			}
		}

		else if (scrapsCount >= 7) // 많은 찌꺼기, 적은 수분
		{
			UE_LOG(LogTemp, Warning, TEXT("Unbalanced. Scrap is more than Water"));

			// 2. 변비 엔딩
			if (exitActor)
			{
				exitActor->bSecondEnding = true;
				exitActor->SetCheckClear(true);
			}
		}

		if (waterCount == 5 && scrapsCount == 5)
		{
			UE_LOG(LogTemp, Warning, TEXT("Very Good!!! Very Good!!! Very Good!!! Very Good!!! Very Good!!! "))

			// 3. 쾌변 엔딩
			if (exitActor)
			{
				exitActor->bThirdEnding = true;
				exitActor->SetCheckClear(true);
			}
		}
	}
}

void AStairs::ShowNextStair()
{
	if (stairIndex < meshComponents.Num())
	{
		UStaticMeshComponent* nextStair = meshComponents[stairIndex];

		if (nextStair)
		{
			// 계단을 활성화
			nextStair->SetVisibility(true);
			nextStair->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			// 랜덤 사운드 재생
			if (stairSounds.Num() > 0)
			{
				int32 RandomIndex = FMath::RandRange(0, stairSounds.Num() - 1);
				UGameplayStatics::PlaySoundAtLocation(this, stairSounds[RandomIndex], GetActorLocation());
			}
			// 다음 계단 인덱스로 이동
			stairIndex++;
		}
	}
}
