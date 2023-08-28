// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

class ABall;
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

	virtual void OnMarked(ATarget* Target);
	virtual void OnMarked(ABall* Ball);
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UBoxComponent* Box;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	bool bIsMarked;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMesh;

	UMaterialInterface* StartingMaterial;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Gets called when target changes color
	UFUNCTION(BlueprintImplementableEvent)
	void OnChangeColor();

private:
	UFUNCTION()
		void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult);

	UFUNCTION()
	void MoveRandomDirection();

	UFUNCTION()
	void StartTimer();


private:
	FTimerHandle MoveDelayTimer;

	float HorizontalImpulseMagnitude;

	float MinVerticalImpulseMagnitude;
	float MaxVerticalImpulseMagnitude;



	bool bTimerExpired;

};
