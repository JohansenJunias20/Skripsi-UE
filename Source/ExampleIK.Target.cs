

using UnrealBuildTool;
using System.Collections.Generic;

public class ExampleIKTarget : TargetRules
{
	public ExampleIKTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ExampleIK" } );
	}
}
