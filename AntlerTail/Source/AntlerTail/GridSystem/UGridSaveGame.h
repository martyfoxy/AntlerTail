#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UGridSaveGame.generated.h"

struct FCellData;

UCLASS()
class UGridSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	int32 Version = 1;

	UPROPERTY()
	TArray<FCellData> Cells;
};
