// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class HardTime2Target : TargetRules
{
	public HardTime2Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		//ExtraModuleNames.Add("HardTime2");
		ExtraModuleNames.Add("htn_planner");
	}
}
