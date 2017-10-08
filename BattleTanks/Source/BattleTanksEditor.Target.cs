// Copyright 2017, Andr�s Herrera, All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTanksEditorTarget : TargetRules
{
	public BattleTanksEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "BattleTanks" } );
	}
}
