// ShooterGame. All Right Reserved.

using UnrealBuildTool;

public class ShooterGame : ModuleRules
{
	public ShooterGame(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
		     "Core",
		     "CoreUObject",
		     "Engine",
		     "InputCore",
		     "Niagara",
		     "PhysicsCore",
		     "GameplayTasks",
		     "NavigationSystem"
		});

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		PublicIncludePaths.AddRange(new string[]
		{
			"ShooterGame/Public/Player", 
			"ShooterGame/Public/Components", 
			"ShooterGame/Public/Dev",
			"ShooterGame/Public/Weapon",
			"ShooterGame/Public/UI",
			"ShooterGame/Public/Animations",
			"ShooterGame/Public/Pickups",
			"ShooterGame/Public/Weapon/Components",
			"ShooterGame/Public/AI",
			"ShooterGame/Public/AI/Tasks",
			"ShooterGame/Public/AI/Services",
			"ShooterGame/Public/AI/EQS",
			"ShooterGame/Public/AI/Decorators",
			"ShooterGame/Public/Menu",
			"ShooterGame/Public/Menu/UI",
			"ShooterGame/Public/Sound"

		}); // пути к хедерам

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
