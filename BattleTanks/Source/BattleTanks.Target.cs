// Copyright 2017, Andrés Herrera, All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class BattleTanksTarget : TargetRules
{
	public BattleTanksTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "BattleTanks" } );
	}
}
