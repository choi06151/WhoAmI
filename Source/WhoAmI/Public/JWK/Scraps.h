#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Scraps.generated.h"

UCLASS()
class WHOAMI_API AScraps : public AActor
{
	GENERATED_BODY()
	
public:	
	AScraps();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


	////////////////////// Component ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TArray<UStaticMeshComponent*> meshComponents;

	///////////////////////////////////////////////////////
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AStairs* stair;

	UPROPERTY(EditAnywhere)
	class USoundWave* scrapSound;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

};
