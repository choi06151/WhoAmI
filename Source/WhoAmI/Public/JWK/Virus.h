#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Virus.generated.h"

UCLASS()
class WHOAMI_API AVirus : public AActor
{
	GENERATED_BODY()
	
public:	
	AVirus();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	////////////////////// Component ////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UBoxComponent* boxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	class UStaticMeshComponent* meshComp;

	/////////////////////////////////////////////////////////
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
