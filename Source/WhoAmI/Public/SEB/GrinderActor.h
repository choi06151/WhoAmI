// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "GrinderActor.generated.h"

UCLASS()
class WHOAMI_API AGrinderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrinderActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//충돌처리
	UFUNCTION()
	void OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMyCompEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UBoxComponent* GrinderComp;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY()
	class AActor* Gauge;
	
	UPROPERTY()
	class AGaugeActor* GaugeInstance;
	
	void IncrementGauge();

	TArray<AActor*> GaugeBarActors;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> GaugeBarMaterial;

	bool isCheck = false;
};
