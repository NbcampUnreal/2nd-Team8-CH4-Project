// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class LastStand : ModuleRules
{
	public LastStand(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "UMG", "AnimGraphRuntime", "Slate", "SlateCore", "NavigationSystem" });
        PublicDependencyModuleNames.AddRange(new string[] { "OnlineSubsystemEOS", "OnlineSubsystem", "OnlineSubsystemUtils" });
		PrivateIncludePaths.Add("LastStand");
        
        PrivateDefinitions.Add("P2PMODE=0");
		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
