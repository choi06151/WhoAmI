// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SEB_Player.generated.h"

UCLASS()
class WHOAMI_API ASEB_Player : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ASEB_Player();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> SEBCapsuleComponent;

	//충돌처리
	UFUNCTION()
	void OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	bool isHold = false;
	bool isPutDown = false;
private:

	UPROPERTY()
	class ATextActor* TextActorInstance;

	UPROPERTY()
	class ACrystalActor* CrystalActorInstance;

	AActor* Text;
	
	void OnClickAButton();

	void OnClickPutDownButton();

	UPROPERTY()
	class AGrinderActor* GrinderActorInstance;
	
	AActor* Grinder;
};
