using UnrealBuildTool;
using System;
using System.IO;

public class dawnOfAges : ModuleRules
{
	public dawnOfAges(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(
			new string[] {
				"dawnOfAges/Public",
				"dawnOfAges/Public/Inventory",
				"dawnOfAges/Public/Crafting",
				"dawnOfAges/Public/Survival",
				"dawnOfAges/Public/Farming",
				"dawnOfAges/Public/Building",
				"dawnOfAges/Public/Combat",
				"dawnOfAges/Public/Profession",
				"dawnOfAges/Public/Story",
				"dawnOfAges/Public/Multiplayer"
			}
		);

		PrivateIncludePaths.AddRange(
			new string[] {
				"dawnOfAges/Private",
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				"CoreUObject",
				"Engine",
				"InputCore",
				"OnlineSubsystem",
				"OnlineSubsystemUtils",
				"Sockets",
				"Networking",
				"Sockets",
				"Json",
				"JsonUtilities"
			}
		);

		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				"OnlineSubsystemUtils",
				"UDPWrapper"
			}
		);

        if (Target.bBuildEditor == true)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] 
                { 
                    "UnrealEd",
                    "EditorStyle",
                    "PropertyEditor"
                }
            );
        }
	}
}