// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrabHandleActor.generated.h"

class UBoxComponent;

UCLASS()
class WHOAMI_API AGrabHandleActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrabHandleActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* HandleMesh;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* InteractionBox;

	bool bIsGrabbed;

	FVector InitialLocation;

	FVector GrabOffset;

	UFUNCTION()
	void OnHandleGrabbed(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	UFUNCTION()
	void OnHandleReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed);

	void HandleMouseMovement();


};
