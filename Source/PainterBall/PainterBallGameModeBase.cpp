// Fill out your copyright notice in the Description page of Project Settings.


#include "PainterBallGameModeBase.h"

void APainterBallGameModeBase::ChangeMarkedTargetsCount(bool bSubtract)
{
	if (!bSubtract)
	{
		MarkedTargetsCount++;
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

