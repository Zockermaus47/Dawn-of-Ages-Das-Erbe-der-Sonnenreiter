using UnrealBuildTool;

[SupportedPlatforms(UnrealPlatformsDescriptor.AllPlatforms)]
public class dawnOfAgesEditorTarget : TargetRules
{
	public dawnOfAgesEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		bBuild = true;
		bBuildEditor = true;
		bBuildWithUnrealDegree = false;

		ExtraModuleNames.Add("dawnOfAges");
	}
}