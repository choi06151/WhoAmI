#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "ExitActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCheckClearChanged);

UCLASS()
class WHOAMI_API AExitActor : public AActor
{
	GENERATED_BODY()

public:
	AExitActor();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	/////////////////////////////// Component ///////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	USphereComponent* sphereComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	UStaticMeshComponent* meshComp;

	/////////////////////////////// 변수 ///////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ending Condition")
	bool bCheckClear = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ending Condition")
	bool bFirstEnding = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ending Condition")
	bool bSecondEnding = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ending Condition")
	bool bThirdEnding = false;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnCheckClearChanged OnCheckClearChanged;


	/////////////////////////////// 소리 ///////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* FirstEndingSound; // 첫 번째 엔딩 사운드

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* ThirdEndingSound; // 두 번째 엔딩 사운드

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* ToiletFlushSound; // 물 내리는 소리

	/////////////////////////////// 카운트 ///////////////////////////////
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Information")
	class ACountInformation* CountInformationActor;
	
	/////////////////////////////// 함수 ///////////////////////////////
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void SetCheckClear(bool bNewCheckClear);

	UFUNCTION()
	void HandleCheckClearChanged();

	// 어떤 엔딩??
	UFUNCTION()
	void CheckEnding();

	// 1.설사 엔딩
	UFUNCTION()
	void FirstEnding();

	// 2. 변비 엔딩
	UFUNCTION()
	void SecondEnding();

	// 3.쾌변 엔딩
	UFUNCTION()
	void ThirdEnding();
};
