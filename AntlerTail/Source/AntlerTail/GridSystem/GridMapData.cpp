// Fill out your copyright notice in the Description page of Project Settings.


#include "GridMapData.h"

#if WITH_EDITOR
#include "GridMapActor.h"
void UGridMapData::PostEditChangeProperty(FPropertyChangedEvent& E)
{
	Super::PostEditChangeProperty(E);
	if (AGridMapActor* Owner = Cast<AGridMapActor>(GetOuter()))
	{
		Owner->RebuildAllHISMs();
	}
}
#endif