// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class RPGImitation : ModuleRules
{
	public RPGImitation(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "UMG", "NavigationSystem", "AIModule", "GameplayTasks", "Slate", "SlateCore", "Sockets", "Networking", "Json", "JsonUtilities" });
	}
}
