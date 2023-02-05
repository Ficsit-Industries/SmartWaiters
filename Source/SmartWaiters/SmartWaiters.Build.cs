using UnrealBuildTool;
using System.IO;
using Tools.DotNETCommon;

public class SmartWaiters: ModuleRules
{
    public SmartWaiters(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		var factoryGamePchPath = new DirectoryReference(Path.Combine(Target.ProjectFile.Directory.ToString(), "Source", "FactoryGame", "Public", "FactoryGame.h"));
        PrivatePCHHeaderFile = factoryGamePchPath.MakeRelativeTo(new DirectoryReference(ModuleDirectory));

		PublicDependencyModuleNames.AddRange(new string[] {
				"Core", "CoreUObject",
	            "Engine",
	            "InputCore","UMG",
				"FactoryGame", "SML"
            });
    }
}