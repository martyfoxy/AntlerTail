#pragma once
#include "EdMode.h"

class FGridEdMode : public FEdMode
{
public:
	const static FEditorModeID EM_Grid;
	FGridEdMode();
	virtual ~FGridEdMode() override {}

	virtual void Enter() override;
	virtual void Exit() override;

	virtual bool UsesToolkits() const override { return true; }
	virtual bool InputKey(FEditorViewportClient* ViewportClient, FViewport* Viewport,FKey Key, EInputEvent Event) override;
	virtual bool MouseMove(FEditorViewportClient* ViewportClient, FViewport* Viewport, int32 X, int32 Y) override;
	virtual void Render(const FSceneView* View, FViewport* Viewport, FPrimitiveDrawInterface* PDI) override;

private:
	TWeakObjectPtr<class AGridMapActor> GridActor;
	FIntPoint HoverCellGridPos = FIntPoint(0,0);
	bool bHasHover = false;
	int32 CurrentType = 0;

	bool ResolveActiveGridActor();
	bool ScreenToWorldOnPlane(FEditorViewportClient* ViewportClient, int32 X, int32 Y, FVector& OutWorld) const;
	void UpdatePreview() const;
	void PlaceCell() const;
	void DeleteCell(FIntPoint Pos) const;
	void ChangeCurrentCellTypeIndex(int32 Delta);
	bool IsAllowedToPlace(FIntPoint Pos) const;
};
