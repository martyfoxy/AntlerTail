#include "LevelGridEditor.h"
#include "EditorModeRegistry.h"
#include "FGridEdMode.h"
#include "Styling/AppStyle.h"

#define LOCTEXT_NAMESPACE "FLevelGridEditorModule"

void FLevelGridEditorModule::StartupModule()
{
    FEditorModeRegistry::Get().RegisterMode<FGridEdMode>(
    	FGridEdMode::EM_Grid,
    	LOCTEXT("LevelGridEditor", "Edit Level Grid"),
    	FSlateIcon(FAppStyle::GetAppStyleSetName(), "MaterialEditor.TogglePreviewGrid"),
    	true,
    	10000);
}

void FLevelGridEditorModule::ShutdownModule()
{
	FEditorModeRegistry::Get().UnregisterMode(FGridEdMode::EM_Grid);
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FLevelGridEditorModule, LevelGridEditor)