// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dodgeball : ModuleRules
{
	public Dodgeball(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
