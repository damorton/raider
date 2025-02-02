// Fill out your copyright notice in the Description page of Project Settings.
//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#pragma once

#include "GameFramework/HUD.h"
#include "RaiderHUD.generated.h"

/**
 * 
 */
UCLASS()
class RAIDER_API ARaiderHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	// The font used to render the text in the HUD.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;

	// Add this function to be able to draw to the HUD!
	virtual void DrawHUD() override;
	
	void DrawHealthbar();
	
};
