#pragma once

#include "CoreMinimal.h"
#include "FCellData.generated.h"

USTRUCT(BlueprintType)
struct FCellData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FIntPoint Position = FIntPoint::ZeroValue;

	UPROPERTY(EditAnywhere)
	int32 Height = 0;

	UPROPERTY(EditAnywhere)
	int32 TypeId = -1;

	UPROPERTY(EditAnywhere)
	FRotator Rotation = FRotator::ZeroRotator;
};
