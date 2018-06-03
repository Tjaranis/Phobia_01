// toturial-continued dev by Tjalfe

using UnrealBuildTool;
using System.Collections.Generic;

public class PhobiaTarget : TargetRules
{
	public PhobiaTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Phobia" } );
	}
}
