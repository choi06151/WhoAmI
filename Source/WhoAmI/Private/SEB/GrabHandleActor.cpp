// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/GrabHandleActor.h"

#include "Components/BoxComponent.h"

// Sets default values
AGrabHandleActor::AGrabHandleActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HandleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HandleMesh"));
	RootComponent = HandleMesh;

	InteractionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBox"));
	InteractionBox->SetupAttachment(RootComponent);

	bIsGrabbed = false;
}

// Called when the game starts or when spawned
void AGrabHandleActor::BeginPlay()
{
	Super::BeginPlay();
	InitialLocation = GetActorLocation();

	// Bind events
	HandleMesh->OnClicked.AddDynamic(this, &AGrabHandleActor::OnHandleGrabbed);
	HandleMesh->OnReleased.AddDynamic(this, &AGrabHandleActor::OnHandleReleased);

}

// Called every frame
void AGrabHandleActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bIsGrabbed)
	{
		HandleMouseMovement();
	}
}

void AGrabHandleActor::OnHandleGrabbed(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bIsGrabbed = true;

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);
		FVector WorldMouseLocation, WorldMouseDirection;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldMouseLocation, WorldMouseDirection);

		// Calculate the grab offset
		GrabOffset = GetActorLocation() - WorldMouseLocation;
	}
}

void AGrabHandleActor::OnHandleReleased(UPrimitiveComponent* TouchedComponent, FKey ButtonPressed)
{
	bIsGrabbed = false;

	// Check if handle was moved far enough to trigger an action
	FVector CurrentLocation = GetActorLocation();
	float ThresholdDistance = 100.0f; // Adjust this value as needed
	if (FVector::Dist(InitialLocation, CurrentLocation) > ThresholdDistance)
	{
		// Trigger desired action
	}
	
	// Reset to initial location or keep the new location
	SetActorLocation(InitialLocation);
}

void AGrabHandleActor::HandleMouseMovement()
{
	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		float MouseX, MouseY;
		PlayerController->GetMousePosition(MouseX, MouseY);
		FVector WorldMouseLocation, WorldMouseDirection;
		PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldMouseLocation, WorldMouseDirection);

		// Set the new location of the handle based on mouse movement
		FVector NewLocation = WorldMouseLocation + GrabOffset;
		SetActorLocation(NewLocation);
	}
}

