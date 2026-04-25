using UnrealBuildTool;

[SupportedPlatforms(UnrealPlatformsDescriptor.AllPlatforms)]
public class dawnOfAgesTarget : TargetRules
{
	public dawnOfAgesTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		bBuild = true;
		bBuildEditor = true;
		bBuildWithUnrealDegree = false;

		ExtraModuleNames.Add("dawnOfAges");
	}
}