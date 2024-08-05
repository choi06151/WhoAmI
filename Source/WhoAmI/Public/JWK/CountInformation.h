#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CountInformation.generated.h"

class UTextRenderComponent;

UCLASS()
class WHOAMI_API ACountInformation : public AActor
{
	GENERATED_BODY()
	
public:	
	ACountInformation();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Count")
	// int waterCount;
	//
	// UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Count")
	// int scrapsCount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Count")
	int totalCount;
	
	UFUNCTION(BlueprintCallable, Category = "Count")
	void UpdateCounts(int newWaterCount, int newScrapsCount);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* TextComponent;
};
