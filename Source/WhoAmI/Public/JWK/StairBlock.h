// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "StairBlock.generated.h"

UCLASS()
class WHOAMI_API AStairBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	AStairBlock();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CheckStair")
	int blockIndex = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
	TArray<UBoxComponent*> boxComponents;

	UFUNCTION(BlueprintCallable)
	void OpenBlock();
};
