#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Water.generated.h"

UCLASS()
class WHOAMI_API AWater : public AActor
{
	GENERATED_BODY()
	
public:	
	AWater();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	////////////////////// Component ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* meshComp;

	/////////////////////////////////////////////////////////
	// UPROPERTY(EditAnywhere,BlueprintReadWrite)
	// class UCollection_Component* collection;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	class AStairs* stair;
	
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	
};
