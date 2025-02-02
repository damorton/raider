//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#pragma once

#include "GameFramework/Character.h"
#include "Monster.generated.h"

class AMeleeWeapon;

UCLASS()
class RAIDER_API AMonster : public ACharacter
{

	//GENERATED_BODY()
	GENERATED_UCLASS_BODY()
public:
	
	// Sets default values for this character's properties
	AMonster();

	//AMonster(const class FObjectInitializer& PCIP);

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
	float m_fSpeed;

	// The MeleeWeapon class the monster uses
	// If this is not set, he uses a melee attack
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPMeleeWeapon;

	// The MeleeWeapon instance (set if the character is using
	// a melee weapon)
	AMeleeWeapon* MeleeWeapon;

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
	
	inline bool isInAttackRange(float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}
	inline bool isInSightRange(float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}

	UFUNCTION(BlueprintCallable, Category = Collision)
	bool isInAttackRangeOfPlayer();
	
	UFUNCTION(BlueprintCallable, Category = Collision)
	void SwordSwung();

	UFUNCTION(BlueprintCallable, Category = Door)
	void applyDamage(float damage);

	float m_fHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem *m_HitParticle;
};
