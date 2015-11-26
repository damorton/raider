// Fill out your copyright notice in the Description page of Project Settings.

#include "Raider.h"
#include "Monster.h"
#include "MeleeWeapon.h"
//#include "Engine.h"
#include "RaiderCharacter.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

AMonster::AMonster(const class FObjectInitializer& PCIP) : Super(PCIP)
{
	Speed = 30;
	HitPoints = 20;
	Experience = 0;
	BPLoot = NULL;
	MeleeWeapon = NULL;
	BaseAttackDamage = 1;
	AttackTimeout = 1.5f;
	TimeSinceLastStrike = 0;
	SightSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("SightSphere"));
	SightSphere->AttachTo(RootComponent);
	AttackRangeSphere = PCIP.CreateDefaultSubobject<USphereComponent>(this, TEXT("AttackRangeSphere"));
	AttackRangeSphere->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	ARaiderCharacter *avatar = Cast<ARaiderCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return;
	FVector toPlayer = avatar->GetActorLocation() -	GetActorLocation();
	
	this->GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction

	float distanceToPlayer = toPlayer.Size();
	// If the player is not in the SightSphere of the monster,
	// go back
	if (distanceToPlayer > SightSphere->GetScaledSphereRadius())
	{
		// If the player is out of sight,
		// then the enemy cannot chase
		return;
	}
	toPlayer /= distanceToPlayer; // normalizes the vector
	
	FRotator Rotation = toPlayer.Rotation();
	const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Speed * DeltaTime);

	// Actually move the monster towards the player a bit
	//AddMovementInput(toPlayer, Speed * DeltaTime);
	// At least face the target
	// Gets you the rotator to turn something
	// that looks in the `toPlayer` direction
	//FRotator toPlayerRotation = toPlayer.Rotation();
	//toPlayerRotation.Pitch = 0; // 0 off the pitch
	//RootComponent->SetWorldRotation(toPlayerRotation);
}

// Called to bind functionality to input
void AMonster::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

void AMonster::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	// instantiate the melee weapon if a bp was selected
	if (BPMeleeWeapon)
	{
		MeleeWeapon = GetWorld()->SpawnActor<AMeleeWeapon>(BPMeleeWeapon, FVector(), FRotator());
		if (MeleeWeapon)
		{
			const USkeletalMeshSocket *meshSocket = (USkeletalMeshSocket*)Mesh->GetSocketByName("RightHandSocket"); // be sure to use correct
			// socket name!
			meshSocket->AttachActor(MeleeWeapon, Mesh);
		}
	}
}

bool AMonster::isInAttackRangeOfPlayer()
{
	ARaiderCharacter *avatar = Cast<ARaiderCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	if (!avatar) return false;

	FVector playerPos = avatar->GetActorLocation();
	FVector toPlayer = playerPos - GetActorLocation();
	float distanceToPlayer = toPlayer.Size();

	return distanceToPlayer < AttackRangeSphere->GetScaledSphereRadius();
}

void AMonster::SwordSwung()
{
	if (MeleeWeapon)
	{
		MeleeWeapon->Swing();
	}
}
