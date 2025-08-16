#include "FGridEdMode.h"
#include "AntlerTail/GridSystem/GridMapActor.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "Selection.h"
#include "EditorViewportClient.h"

const FEditorModeID FGridEdMode::EM_Grid = FName(TEXT("EM_Grid"));

FGridEdMode::FGridEdMode() : FEdMode()
{
	
}

void FGridEdMode::Enter()
{
	FEdMode::Enter();
	ResolveActiveGridActor();
}

void FGridEdMode::Exit()
{
	FEdMode::Exit();
}

bool FGridEdMode::InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport, FKey Key, EInputEvent Event)
{
	if (!GridActor.IsValid()) return false;

	if (Event == IE_Pressed)
	{
		if (Key == EKeys::LeftMouseButton)
		{
			PlaceCell();
			return true;
		}

		if (Key == EKeys::MouseScrollUp)
		{
			ChangeCurrentCellTypeIndex(1);
			return true;
		}
		
		if (Key == EKeys::MouseScrollDown)
		{
			ChangeCurrentCellTypeIndex(-1);
			return true;
		}

		if (Key == EKeys::RightMouseButton)
		{
			DeleteCell(HoverCellGridPos);
			return true;
		}
	}
	return FEdMode::InputKey(ViewportClient, Viewport, Key, Event);
}

bool FGridEdMode::MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y)
{
	if (!GridActor.IsValid())
	{
		ResolveActiveGridActor();
		return false;
	}

	FVector ResultPos;
	bHasHover = ScreenToWorldOnPlane(ViewportClient, X, Y, ResultPos);
	if (bHasHover)
	{
		HoverCellGridPos = GridActor->WorldToGrid(ResultPos);
		UpdatePreview();
		ViewportClient->Invalidate();
	}
	return false;
}

void FGridEdMode::Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI)
{
	FEdMode::Render(View, Viewport, PDI);
	if (!GridActor.IsValid() || !bHasHover) return;
	auto* Grid = GridActor.Get();
	
	const FVector C = Grid->GridToWorld(HoverCellGridPos) + FVector(0,0,2);
	const float S = Grid->Data ? Grid->Data->CellSize : 100.f;
	const FVector X(S * 0.5f,0,0), Y(0,S * 0.5f,0);

	FLinearColor Col = IsAllowedToPlace(HoverCellGridPos) ?
		FLinearColor(0.2f, 0.8f, 0.2f) :
		FLinearColor(0.8f, 0.2f, 0.2f);
	
	PDI->DrawLine(C - X - Y, C + X - Y, Col, SDPG_Foreground);
	PDI->DrawLine(C + X - Y, C + X + Y, Col, SDPG_Foreground);
	PDI->DrawLine(C + X + Y, C - X + Y, Col, SDPG_Foreground);
	PDI->DrawLine(C - X + Y, C - X - Y, Col, SDPG_Foreground);
}

bool FGridEdMode::ResolveActiveGridActor()
{
	GridActor = nullptr;
	if (!GEditor) return false;

	USelection* Sel = GEditor->GetSelectedActors();
	if (!Sel) return false;

	for (FSelectionIterator It(*Sel); It; ++It)
	{
		if (AGridMapActor* Grid = Cast<AGridMapActor>(*It))
		{
			GridActor = Grid;
			break;
		}
	}
	return GridActor.IsValid();
}

bool FGridEdMode::ScreenToWorldOnPlane(FEditorViewportClient* ViewportClient, int32 X, int32 Y, FVector& OutWorld) const
{
	if (!GridActor.IsValid()) return false;
	
	FSceneViewFamilyContext ViewFamily(
		FSceneViewFamily::ConstructionValues(
		ViewportClient->Viewport,
		ViewportClient->GetScene(),
		ViewportClient->EngineShowFlags));
	
	FSceneView* View = ViewportClient->CalcSceneView(&ViewFamily);
	if (!View) return false;

	const FViewportCursorLocation Cursor(View, ViewportClient, X, Y);
	const FVector RayO = Cursor.GetOrigin();
	const FVector RayD = Cursor.GetDirection();
	const FPlane Plane(GridActor->GetActorLocation(), FVector::UpVector);
	const FVector RayEnd = RayO + RayD * 100000.f;
	return FMath::SegmentPlaneIntersection(RayO, RayEnd, Plane, OutWorld);
}

void FGridEdMode::UpdatePreview() const
{
	if (!GridActor.IsValid()) return;
	auto* Grid = GridActor.Get();

	if (Grid->CellDefinitions.IsValidIndex(CurrentType))
	{
		UCellDefinition* CellDefinition = Grid->CellDefinitions[CurrentType];
		UStaticMesh* CurrentMesh = CellDefinition->Mesh;
		UMaterialInterface* CurrentMaterial = CellDefinition->Material;
		
		Grid->PreviewMesh->SetStaticMesh(CurrentMesh);
		Grid->PreviewMesh->SetMaterial(0, CurrentMaterial);
		Grid->PreviewMesh->SetWorldLocation(Grid->GridToWorld(HoverCellGridPos) + CellDefinition->MeshOffset);
		Grid->PreviewMesh->SetHiddenInGame(false);
		Grid->PreviewMesh->SetVisibility(true, true);
	}
}

void FGridEdMode::PlaceCell() const
{
	if (!GridActor.IsValid()) return;
	auto* A = GridActor.Get();
	
	const FIntPoint P = HoverCellGridPos;
	UGridMapData* GridData = A->Data;
	
	if (!IsAllowedToPlace(P)) return;

	FCellData C;
	C.Position = P;
	C.TypeId = CurrentType;
	C.Height = 0;
	C.Rotation = FRotator::ZeroRotator;
	
	GridData->Modify();
	GridData->Cells.Add(C);

	A->EnsureHISMForTypeId(CurrentType);
	A->HISMByType[CurrentType]->AddInstance(FTransform(C.Rotation, A->GridToWorld(P)));
}

void FGridEdMode::DeleteCell(FIntPoint Pos) const
{
	if (!GridActor.IsValid()) return;
	auto* A = GridActor.Get();
	
	UGridMapData* GridData = A->Data;

	if (!GridData->HasCell(Pos)) return;

	for (int i = 0; i< GridData->Cells.Num(); i++)
	{
		if (GridData->Cells[i].Position == Pos)
		{
			A->Data->Modify();
			A->Data->Cells.RemoveAtSwap(i);

			A->RebuildAllHISMs();
			UpdatePreview();
		}
	}
}

void FGridEdMode::ChangeCurrentCellTypeIndex(int32 Delta)
{
	if (!GridActor.IsValid()) return;
	auto* A = GridActor.Get();
	
	const int32 N = A->CellDefinitions.Num();
	if (N <= 0) return;
	
	CurrentType = (CurrentType + Delta) % N;
	if (CurrentType < 0) CurrentType += N;
	
	UpdatePreview();
}

bool FGridEdMode::IsAllowedToPlace(FIntPoint Pos) const
{
	if (!GridActor.IsValid()) return false;
	auto* A = GridActor.Get();
	
	UGridMapData* GridData = A->Data;
	
	const bool IsFirstCell = GridData->Cells.Num() == 0;
	auto HasNeighbour = [&](FIntPoint d)
	{
		return GridData->HasCell(Pos + d);
	};

	if (GridData->HasCell(Pos)) return false;
	
	return IsFirstCell ||
		HasNeighbour({1,0}) ||
		HasNeighbour({-1,0}) ||
		HasNeighbour({0,1}) ||
		HasNeighbour({0,-1});
}
