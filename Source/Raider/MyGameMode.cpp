// Fill out your copyright notice in the Description page of Project Settings.

#include "Raider.h"
#include "MyGameMode.h"
#include "RaiderPlayerController.h"
#include "RaiderCharacter.h"

AMyGameMode::AMyGameMode()
{

	// use our custom PlayerController class
	PlayerControllerClass = ARaiderPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/Player"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

}

