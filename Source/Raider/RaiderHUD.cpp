// Fill out your copyright notice in the Description page of Project Settings.
//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#include "Raider.h"
#include "RaiderHUD.h"
#include "RaiderCharacter.h"
#include "Engine.h"

void ARaiderHUD::DrawHUD()
{
	// call superclass DrawHUD() function first
	Super::DrawHUD();
		
	DrawHealthbar();
}

void ARaiderHUD::DrawHealthbar()
{
	// Draw the healthbar.
	ARaiderCharacter *avatar = Cast<ARaiderCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	float percHp = avatar->Hp / avatar->MaxHp;
	DrawRect(FLinearColor(0, 0, 0, 1), Canvas->SizeX - barWidth - barPad - barMargin,
		Canvas->SizeY - barHeight - barPad - barMargin, barWidth + 2 * barPad, barHeight + 2 * barPad);
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), Canvas->SizeX - barWidth - barMargin,
		Canvas->SizeY - barHeight - barMargin, barWidth*percHp, barHeight);

}

