

using UnrealBuildTool;

public class ExampleIK : ModuleRules
{
	public ExampleIK(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] 
			{ "Core", "CoreUObject", "Engine", "InputCore" ,"OnlineSubsystem","OnlineSubsystemSteam","OnlineSubsystemEOS","VoiceChat"});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

	}
}
