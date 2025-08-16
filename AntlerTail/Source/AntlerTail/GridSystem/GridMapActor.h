#pragma once

#include "CoreMinimal.h"
#include "GridMapData.h"
#include "UCellDefinition.h"
#include "GameFramework/Actor.h"
#include "GridMapActor.generated.h"

class UHierarchicalInstancedStaticMeshComponent;

UCLASS()
class ANTLERTAIL_API AGridMapActor : public AActor
{
	GENERATED_BODY()

public:
	AGridMapActor();

	UPROPERTY(EditAnywhere, Instanced, Category="Grid")
	UGridMapData* Data;

	UPROPERTY(EditAnywhere, Category="Grid")
	TArray<UCellDefinition*> CellDefinitions;

	UPROPERTY(VisibleAnywhere)
	USceneComponent* SceneRoot;

	UPROPERTY(Transient)
	TMap<int, UHierarchicalInstancedStaticMeshComponent*> HISMByType;

	UPROPERTY(Transient)
	UStaticMeshComponent* PreviewMesh;

	FVector GridToWorld(const FIntPoint& Pos) const
	{
		const float CellSize = Data ? Data->CellSize : 100.f;
		return GetActorLocation() + FVector(Pos.X * CellSize, Pos.Y * CellSize, 0.0f);
	}

	FIntPoint WorldToGrid(const FVector& Pos) const
	{
		const float CellSize = Data ? Data->CellSize : 100.f;
		const FVector LocalPos = Pos - GetActorLocation();
		return FIntPoint(FMath::FloorToInt(LocalPos.X / CellSize), FMath::FloorToInt(LocalPos.Y / CellSize));
	}

	//Creates HISM for the given TypeId of cell
	void EnsureHISMForTypeId(int32 TypeId);

	//Forcibly rebuilds all HISMs
	void RebuildAllHISMs();

#if WITH_EDITOR
	virtual void PostLoad() override;
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void PostEditUndo() override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& E) override;
	void OnAnyObjectPropertyChanged(UObject* Obj, FPropertyChangedEvent& E);
	virtual void PostInitProperties() override;
	virtual void BeginDestroy() override;
#endif
};
