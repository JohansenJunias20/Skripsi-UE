

using UnrealBuildTool;
using System.Collections.Generic;

public class ExampleIKEditorTarget : TargetRules
{
	public ExampleIKEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ExampleIK" } );
	}
}
