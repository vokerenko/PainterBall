// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterBallGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void APainterBallGameModeBase::ChangeMarkedTargetsCount(bool bSubtract)
{
	if (!bSubtract)
	{
		MarkedTargetsCount++;
		if (MarkedTargetsCount == TotalTargetsCount)
		{
			OnWin();
		}
	}
	else
	{
		MarkedTargetsCount--;
	}

}
void APainterBallGameModeBase::ChangeMarkedPurifiersCount(bool bSubtract)
{
	if (!bSubtract)
	{
		MarkedPurifiersCount++;
	}
	else
	{
		MarkedPurifiersCount--;
	}
	
}

