#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Collection_Component.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WHOAMI_API UCollection_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCollection_Component();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, Category = "Collection")
	int32 waterCount = 0;

	UPROPERTY(EditAnywhere, Category = "Collection")
	int32 scrapsCount = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class AStairs* stairs;
	
	UFUNCTION()
	void CheckTotalCount();

	UFUNCTION()
	void IncreaseWater();
	
	UFUNCTION()
	void IncreaseScraps();
};
