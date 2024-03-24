// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Dia : ModuleRules
{
	public Dia(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "NavigationSystem", "AIModule", "Niagara", "EnhancedInput" });
        PublicDependencyModuleNames.AddRange(new string[] { "GameplayAbilities"});
        PublicDependencyModuleNames.AddRange(new string[] { "UMG"});

        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayTags", "GameplayTasks" });
        PrivateDependencyModuleNames.AddRange(new string[] { "GameplayMessageRuntime" });
        PrivateDependencyModuleNames.AddRange(new string[] { "ActorSequence" });
        PrivateDependencyModuleNames.AddRange(new string[] { "OnlineSubsystem", "OnlineSubsystemNull", "OnlineSubsystemUtils" });
    }
}
