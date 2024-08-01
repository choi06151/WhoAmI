#include "JWK/Stairs.h"

#include "JWK/StairBlock.h"

AStairs::AStairs()
{
	PrimaryActorTick.bCanEverTick = true;
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempMesh(TEXT("/Script/Engine.StaticMesh'/Game/Crystal_cave/Meshes/Stairs/SM_stairs_01.SM_stairs_01'"));

	for (int i = 0; i < 5; i++)		// n번 계단 meshComp 추가
	{

		////////////////////////////////////// 계단 //////////////////////////////////////
		FString meshCompName = FString::Printf(TEXT("meshComp_%d"), i + 1);	// 1번 부터
		UStaticMeshComponent* newMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(*meshCompName);
		
		if (tempMesh.Succeeded())
			newMeshComp->SetStaticMesh(tempMesh.Object);

		meshComponents.Add(newMeshComp);

		newMeshComp->SetVisibility(true);
		newMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		/////////////////////////////////////////////////////////////////////////////////
	}
}

void AStairs::BeginPlay()
{
	Super::BeginPlay();

	// 게임이 시작될 때 모든 메시를 비활성화
	for (UStaticMeshComponent* meshComp : meshComponents)
	{
		if (meshComp)
		{
			meshComp->SetVisibility(false);
			meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}
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
}

void AStairs::CheckScrapsOverlap()
{
	scrapsCount++;
	UE_LOG(LogTemp, Warning, TEXT("scrapsCount : %d"), scrapsCount);

	CheckTotalCount();
}

void AStairs::CheckTotalCount()
{
	int totalCount = waterCount + scrapsCount;

	if(totalCount % 2 == 0 && totalCount <= 10)
	{
		ShowNextStair();
	}
	
	// 엔딩 조건 체크
	if (totalCount == 10)
	{
		if (waterCount >= 7) // 많은 수분, 적은 찌꺼기
		{
			UE_LOG(LogTemp, Warning, TEXT("Unbalanced. Water is more than Scraps"));

			// 1. 설사 엔딩
		}

		else if (scrapsCount >= 7) // 많은 찌꺼기, 적은 수분
		{
			UE_LOG(LogTemp, Warning, TEXT("Unbalanced. Scrap is more than Water"));

			// 2. 변비 엔딩
		}

		if (waterCount == 5 && scrapsCount == 5)
		{
			UE_LOG(LogTemp, Warning, TEXT("Very Good!!! Very Good!!! Very Good!!! Very Good!!! Very Good!!! "))

			// 3. 쾌변 엔딩
		}
	}
}

void AStairs::ShowNextStair()
{
	if(stairIndex < meshComponents.Num())
	{
		UStaticMeshComponent* nextStair = meshComponents[stairIndex];

		if(nextStair)
		{
			// 계단을 활성화
			nextStair->SetVisibility(true);
			nextStair->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

			// 다음 계단 인덱스로 이동
			stairIndex++;
		}
	}
}
