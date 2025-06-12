// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class BossDesign : ModuleRules
{
	public BossDesign(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
