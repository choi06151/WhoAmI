// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/GaugeActor.h"

#include "Components/WidgetComponent.h"

// Sets default values
AGaugeActor::AGaugeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	
	

}

// Called when the game starts or when spawned
void AGaugeActor::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void AGaugeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

