// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HardTime2 : ModuleRules
{
	public HardTime2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "AIModule" });
		// TODO it's not clear if we need all these lines. It may be best to either add the htn_planner module, or include it's sources. But probably not both.
		// Then revisit bUseRTTI as well.
		//PublicDependencyModuleNames.Add("htn_planner");
		bUseRTTI = true;

		PublicIncludePaths.Add("C:/Users/triha/OneDrive/Documents/Unreal Projects/HardTime2 4.26/Source/htn_planner/Public");
		PublicIncludePaths.Add("C:/Users/triha/OneDrive/Documents/Unreal Projects/HardTime2 4.26/Source/htn_planner/Private");
	}
}
