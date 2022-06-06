// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Radiance : ModuleRules
{
	public Radiance(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "UMG", "GameplayTasks", "NavigationSystem", "AIModule", "Niagara",
															"LevelSequence", "MovieScene",  "MediaAssets"});

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" } );

		PublicIncludePaths.AddRange(new string[] {
            System.IO.Path.Combine("/Engine/Plugins/FX/Niagara/Source/Niagara/Public/NiagaraFunctionLibrary.h", "Niagara")
		});
	}
}
