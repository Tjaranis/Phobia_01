// toturial-continued dev by Tjalfe

using UnrealBuildTool;
using System.Collections.Generic;

public class PhobiaEditorTarget : TargetRules
{
	public PhobiaEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Phobia" } );
	}
}
