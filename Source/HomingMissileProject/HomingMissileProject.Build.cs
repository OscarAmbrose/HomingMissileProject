// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class HomingMissileProject : ModuleRules
{
	public HomingMissileProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"HomingMissileProject",
			"HomingMissileProject/Variant_Platforming",
			"HomingMissileProject/Variant_Combat",
			"HomingMissileProject/Variant_Combat/AI",
			"HomingMissileProject/Variant_SideScrolling",
			"HomingMissileProject/Variant_SideScrolling/Gameplay",
			"HomingMissileProject/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
