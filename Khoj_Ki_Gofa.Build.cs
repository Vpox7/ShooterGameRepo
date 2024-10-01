// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Khoj_Ki_Gofa : ModuleRules
{
	public Khoj_Ki_Gofa(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "UMG"});
       
    }
}
