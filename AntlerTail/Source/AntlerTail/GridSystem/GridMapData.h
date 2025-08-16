#pragma once

#include "CoreMinimal.h"
#include "FCellData.h"
#include "UObject/Object.h"
#include "GridMapData.generated.h"

UCLASS()
class ANTLERTAIL_API UGridMapData : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float CellSize = 100.0f;

	UPROPERTY(EditAnywhere)
	TArray<FCellData> Cells;

	bool HasCell(FIntPoint Pos) const
	{
		return Cells.ContainsByPredicate([&](const FCellData& C){ return C.Position == Pos; });
	}

	bool TryGetCellAtPos(FIntPoint Pos, FCellData& OutCell) const
	{
		const FCellData* Cell = Cells.FindByPredicate([&](FCellData& C){ return C.Position == Pos; });
		if (Cell)
		{
			OutCell = *Cell;
			return true;
		}
		return false;
	}
	

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& E) override;
#endif
};
