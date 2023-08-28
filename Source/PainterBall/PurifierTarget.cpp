// Fill out your copyright notice in the Description page of Project Settings.


#include "PurifierTarget.h"
#include "PainterBallGameModeBase.h"
#include "Kismet/GameplayStatics.h"


void APurifierTarget::OnMarked(ATarget* Target)
{
	if (APurifierTarget* Purifier = Cast<APurifierTarget>(Target))
	{
		if (bIsMarked && !Purifier->bIsMarked)
		{
			OnChangeColor();
			bIsMarked = false;
			if (APainterBallGameModeBase* GM = Cast<APainterBallGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
			{
				GM->ChangeMarkedPurifiersCount(true);
				GM->ChangeMarkedTargetsCount(true);
			}
		}
	}
}

void APurifierTarget::OnMarked(ABall* Ball)
{
	if (!bIsMarked)
	{
		if (APainterBallGameModeBase* GM = Cast<APainterBallGameModeBase>(UGameplayStatics::GetGameMode(GetWorld())))
		{
			GM->ChangeMarkedPurifiersCount();
		}
	}
	Super::OnMarked(Ball);
}