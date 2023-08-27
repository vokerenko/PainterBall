// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"
#include "Components/BoxComponent.h"
#include "Ball.h"

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
		StaticMesh->SetMaterial(0, Ball->GetStaticMeshMaterial());
		
	}
	else if (ATarget* Target = Cast<ATarget>(OtherActor))
	{
		if (Target != this)
		{

		}
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

