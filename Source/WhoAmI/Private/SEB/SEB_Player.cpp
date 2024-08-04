// Fill out your copyright notice in the Description page of Project Settings.


#include "SEB/SEB_Player.h"

#include "EngineUtils.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "SEB/CrystalActor.h"
#include "SEB/GrinderActor.h"
#include "SEB/TextActor.h"

// Sets default values   
ASEB_Player::ASEB_Player()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SEBCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("EBCapsuleComponent"));
}

// Called when the game starts or when spawned
void ASEB_Player::BeginPlay()
{
	Super::BeginPlay();

	SEBCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ASEB_Player::OnMyCompBeginOverlap);
	
	TSubclassOf<AActor> ActorClass = ATextActor::StaticClass();
	Text  = UGameplayStatics::GetActorOfClass(GetWorld(), ActorClass);

	TextActorInstance = Cast<ATextActor>(Text);

	TSubclassOf<AActor> GrinderActorClass = AGrinderActor::StaticClass();
	Grinder  = UGameplayStatics::GetActorOfClass(GetWorld(), GrinderActorClass);
	GrinderActorInstance = Cast<AGrinderActor>(Grinder);
}

// Called every frame
void ASEB_Player::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASEB_Player::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("ClickAButton", IE_Pressed, this, &ASEB_Player::OnClickAButton);
	PlayerInputComponent->BindAction("PutDownCrystal", IE_Pressed, this, &ASEB_Player::OnClickPutDownButton);

}

void ASEB_Player::OnMyCompBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	/*if ( OtherActor->IsA<ACrystalActor>() )
	{
		UE_LOG(LogTemp, Error, TEXT("ACrystalActor"));
		CrystalActorInstance = Cast<ACrystalActor>(OtherActor);
		
		CrystalActorInstance->DestroyCrystal();
		
	}*/
}

void ASEB_Player::OnClickAButton()
{
	UE_LOG(LogTemp, Error,  TEXT("눌렸다") );
	if (Text)
	{
		UE_LOG(LogTemp, Error,  TEXT("눌렸다22") );
		//TextActorInstance->InfoText->SetText(FText::FromString("가나다"));
		TextActorInstance->ClickAButton();
	}
}

void ASEB_Player::OnClickPutDownButton()   
{
	UE_LOG(LogTemp, Error, TEXT("2번 버튼이 눌렸다."));
	if(isHold) // 크리스탈을 잡고 있다면
	{
		if(GrinderActorInstance->isCheck)
		{
			UE_LOG(LogTemp, Error, TEXT("크리스탈도 잡고, 그라인더 앞에 있구나."));
			isHold = false;
			UE_LOG(LogTemp, Error, TEXT("isHold : %d"), isHold);
			GrinderActorInstance->IncrementGauge();
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("크리스탈은 잡았지만 그라인더 앞에 있지 않구나"));
		}
	}
	
	else
	{
		UE_LOG(LogTemp, Error, TEXT("아직 크리스탈을 잡지 않았잖아 너"));
	}
}

