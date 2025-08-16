using UnrealBuildTool;

public class LevelGridEditor : ModuleRules
{
    public LevelGridEditor(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core",
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "InputCore",
                "ApplicationCore",
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "UnrealEd",
                "EditorFramework",
                "LevelEditor",
                "PropertyEditor",
                "Projects",
                "RenderCore",
                "RHI",
                "InteractiveToolsFramework",
                "ToolMenus",
                "AppFramework",
                "EditorSubsystem",
                "AntlerTail"
            }
        );
    }
}