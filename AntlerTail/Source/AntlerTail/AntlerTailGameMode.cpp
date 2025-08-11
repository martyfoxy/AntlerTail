// Copyright Epic Games, Inc. All Rights Reserved.

#include "AntlerTailGameMode.h"
#include "AntlerTailCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAntlerTailGameMode::AAntlerTailGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
