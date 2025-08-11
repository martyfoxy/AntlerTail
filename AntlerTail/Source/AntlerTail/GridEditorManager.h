#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GridSystem/FCellData.h"
#include "GridEditorManager.generated.h"

class UCellDefinition;
class UStaticMeshComponent;
class UMaterialInterface;

UCLASS()
class ANTLERTAIL_API AGridEditorManager : public AActor
{
	GENERATED_BODY()
	
public:
	AGridEditorManager();

	UPROPERTY(EditAnywhere, Category="Grid")
	float GridSize = 100.0f;

	UPROPERTY(EditAnywhere, Category="Grid")
	TArray<UCellDefinition*> PlacebleCells;

	UPROPERTY(EditAnywhere, Category="Preview")
	UStaticMeshComponent* Preview;

	UPROPERTY(EditAnywhere, Category="Preview")
	UMaterialInterface* PreviewMaterial;

	TMap<FIntPoint, FCellData> Cells;
	int32 CurrentCellTypeId = -1;
	bool bHasFirstCellPlaces = false;

	void PlaceUnderCursor();
	void NextType(int32 Delta);
	
protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
