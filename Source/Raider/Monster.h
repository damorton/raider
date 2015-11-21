// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Monster.generated.h"

UCLASS()
class RAIDER_API AMonster : public ACharacter
{
	GENERATED_BODY()
	//GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's properties
	AMonster();

	AMonster(const class FObjectInitializer& PCIP);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// For melee weapon
	virtual void PostInitializeComponents() override;
	
	// How fast he is
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;

	// The hitpoints the monster has
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float HitPoints;

	// Experience gained for defeating
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 Experience;

	// Blueprint of the type of item dropped by the monster
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPLoot;

	// The amount of damage attacks do
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackDamage;
	
	// Amount of time the monster needs to rest in seconds
	// between attacking
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float AttackTimeout;
	
	// Time since monster's last strike, readable in blueprints
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastStrike;
	
	// Range for his sight
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;
	
	// Range for his attack. Visualizes as a sphere in editor,
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* AttackRangeSphere;

	// The MeleeWeapon class the monster uses
	// If this is not set, he uses a melee attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPMeleeWeapon;

	// The MeleeWeapon instance (set if the character is using
	// a melee weapon)
	AActor* MeleeWeapon;
	
};
