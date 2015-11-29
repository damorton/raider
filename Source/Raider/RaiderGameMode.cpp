// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#include "Raider.h"
#include "RaiderGameMode.h"
#include "RaiderPlayerController.h"
#include "RaiderCharacter.h"

ARaiderGameMode::ARaiderGameMode()
{
	
	// use our custom PlayerController class
	PlayerControllerClass = ARaiderPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Raider/Blueprints/Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	
}