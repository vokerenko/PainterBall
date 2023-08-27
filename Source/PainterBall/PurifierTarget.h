// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "PurifierTarget.generated.h"

/**
 * 
 */
UCLASS()
class PAINTERBALL_API APurifierTarget : public ATarget
{
	GENERATED_BODY()

private:
	virtual void OnMarked(ATarget* Target) override;
	virtual void OnMarked(ABall* Ball) override;
};
