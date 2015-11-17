// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Raider.h"
#include "RaiderGameMode.h"
#include "RaiderPlayerController.h"
#include "RaiderCharacter.h"

ARaiderGameMode::ARaiderGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ARaiderPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}