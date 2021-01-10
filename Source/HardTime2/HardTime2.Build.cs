// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HardTime2 : ModuleRules
{
	public HardTime2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule" });

		//PublicIncludePaths.Add("C:/Users/triha/OneDrive/Documents/Unreal Projects/HardTime2 4.26/Source/imports");
		//PublicIncludePaths.Add("C:/Users/triha/OneDrive/Documents/Unreal Projects/HardTime2 4.26/Source/htn_planner/htn_planner/Public");
	}
}
