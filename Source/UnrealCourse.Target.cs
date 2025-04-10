// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class UnrealCourseTarget : TargetRules
{
	public UnrealCourseTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.Latest;
        IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("UnrealCourse");
	}
}
