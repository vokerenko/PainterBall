// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PainterBallGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class PAINTERBALL_API APainterBallGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	void ChangeMarkedTargetsCount(bool bSubtract = false);
	void ChangeMarkedPurifiersCount(bool bSubtract = false);
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 MarkedTargetsCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 MarkedPurifiersCount = 0;
	
};