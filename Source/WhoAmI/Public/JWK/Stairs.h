#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Stairs.generated.h"

UCLASS()
class WHOAMI_API AStairs : public AActor
{
	GENERATED_BODY()

public:
	AStairs();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	//////////////////// Component ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TArray<UStaticMeshComponent*> meshComponents;


	////////////////////// 수집 관련 변수 ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int waterCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int scrapsCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int stairIndex = 0;

	UPROPERTY(EditAnywhere)
	TArray<AActor*> StairsActor;

	UPROPERTY(EditAnywhere)
	class AStairBlock* stairBlock;

	UPROPERTY(EditAnywhere)
	class AExitActor* exitActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	TArray<USoundWave*> stairSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	class USoundBase* caveSound;
	
	////////////////////// 수집 관련 함수 ////////////////////////
	UFUNCTION(BlueprintCallable)
	void CheckWaterOverlap();

	UFUNCTION(BlueprintCallable)
	void CheckScrapsOverlap();

	UFUNCTION(BlueprintCallable)
	void CheckTotalCount();

	UFUNCTION()
	void ShowNextStair();
};
