// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/BoxComponent.h"
#include "Ball.h"
#include "PurifierTarget.h"
#include "PainterBallGameModeBase.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATarget::ATarget()
	: HorizontalImpulseMagnitude( 400.0f )
	, MinVerticalImpulseMagnitude( 200.0f )
	, MaxVerticalImpulseMagnitude( 300.0f )
	, bIsMarked( false )
	, bTimerExpired( true )
{

	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cube"));
	SetRootComponent(StaticMesh);
	StaticMesh->SetSimulatePhysics(true);

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	Box->SetupAttachment(StaticMesh);

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this, &ATarget::OnBoxBeginOverlap);
	StartingMaterial = StaticMesh->GetMaterial(0);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bTimerExpired)
	{
		bTimerExpired = false;
		StartTimer();
	}
}

void ATarget::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{	
	if (ABall* Ball = Cast<ABall>(OtherActor))
	{
		OnMarked(Ball);
	}
	else if (ATarget* Target = Cast<ATarget>(OtherActor))
	{
		OnMarked(Target);
	}
}

void ATarget::MoveRandomDirection()
{
	FVector Impulse = FVector::ZeroVector;
	Impulse.X = FMath::RandRange(-HorizontalImpulseMagnitude, HorizontalImpulseMagnitude);
	Impulse.Y = FMath::RandRange(-HorizontalImpulseMagnitude, HorizontalImpulseMagnitude);
	Impulse.Z = FMath::RandRange(MinVerticalImpulseMagnitude, MaxVerticalImpulseMagnitude);
	StaticMesh->AddImpulse(Impulse, NAME_None, true);
	bTimerExpired = true;
}

void ATarget::StartTimer()
{
	float Duration = 1.0f;
	GetWorldTimerManager().ClearTimer(MoveDelayTimer);
	GetWorldTimerManager().SetTimer(MoveDelayTimer, this, &ATarget::MoveRandomDirection, Duration);	
}

void ATarget::OnMarked(ATarget* Target)
{
	if (Target->bIsMarked && !bIsMarked)
	{
		StaticMesh->SetMaterial(0, Target->StaticMesh->GetMaterial(0));
		bIsMarked = true;
		if (APainterBallGameModeBase* GM = Cast<APainterBallGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			GM->ChangeMarkedTargetsCount();
		}
	}
	else if (APurifierTarget* Purifier = Cast<APurifierTarget>(Target))
	{
		if (bIsMarked && !Purifier->bIsMarked)
		{
			StaticMesh->SetMaterial(0, StartingMaterial);
			bIsMarked = false;
			if (APainterBallGameModeBase* GM = Cast<APainterBallGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				GM->ChangeMarkedTargetsCount(true);
			}
		}
	}
}
void ATarget::OnMarked(ABall* Ball)
{
	if (!bIsMarked)
	{
		StaticMesh->SetMaterial(0, Ball->GetStaticMeshMaterial());
		bIsMarked = true;
		if (APainterBallGameModeBase* GM = Cast<APainterBallGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			GM->ChangeMarkedTargetsCount();
		}
	}

}

