// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "GaugeActor.generated.h"

UCLASS()
class WHOAMI_API AGaugeActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGaugeActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* GaugeText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* MaxGaugeText;

	void OpenDoor(float DeltaTime);

	AActor* Door;
	
	FVector StartPosition;
	FVector TargetPosition;

	float DoorOpeningSpeed = 1000.0f;
	bool bIsOpening = false;

};
