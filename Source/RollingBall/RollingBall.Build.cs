// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RollingBall : ModuleRules
{
	public RollingBall(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay",
			"EnhancedInput", "NavigationSystem", "AIModule", "GameplayTasks" });
	}
}
