// Copyright Epic Games, Inc. All Rights Reserved.

#include "CommandBattleRPGBaseGameMode.h"
#include "CommandBattleRPGBaseCharacter.h"
#include "UObject/ConstructorHelpers.h"

ACommandBattleRPGBaseGameMode::ACommandBattleRPGBaseGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
