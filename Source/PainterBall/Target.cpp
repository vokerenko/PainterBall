// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

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
}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();
	
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

