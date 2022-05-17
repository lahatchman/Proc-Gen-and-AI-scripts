// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProcGen_and_AI : ModuleRules
{
	public ProcGen_and_AI(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay" });
	}
}
