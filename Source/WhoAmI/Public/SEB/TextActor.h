﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Actor.h"
#include "TextActor.generated.h"

UCLASS()
class WHOAMI_API ATextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATextActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTextRenderComponent* InfoText;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UMaterial> textMtr;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UFont> textFont;


	void ClickAButton();
};
