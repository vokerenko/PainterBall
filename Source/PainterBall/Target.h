// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class UBoxComponent;
UCLASS()
class PAINTERBALL_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* Box;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMesh;

	UFUNCTION()
	void MoveRandomDirection();

	UFUNCTION()
	void StartTimer();

	FTimerHandle MoveDelayTimer;

	float HorizontalImpulseMagnitude;

	float MinVerticalImpulseMagnitude;
	float MaxVerticalImpulseMagnitude;

	bool bIsMarked;
	bool bTimerExpired;

};
