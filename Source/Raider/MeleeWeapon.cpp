//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#include "Raider.h"
#include "MeleeWeapon.h"
#include "Monster.h"
#include "Engine.h"
#include "RaiderCharacter.h"



AMeleeWeapon::AMeleeWeapon(const class FObjectInitializer& PCIP) :
Super(PCIP)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttackDamage = 5;
	Swinging = false;
	WeaponHolder = NULL;
	Mesh = PCIP.CreateDefaultSubobject<UStaticMeshComponent>(this,
		TEXT("Mesh"));
	RootComponent = Mesh;
	ProxBox = PCIP.CreateDefaultSubobject<UBoxComponent>(this,
		TEXT("ProxBox"));
	ProxBox->OnComponentBeginOverlap.AddDynamic(this,
		&AMeleeWeapon::Prox);
	ProxBox->AttachTo(RootComponent);
}

void AMeleeWeapon::Prox_Implementation(AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	// don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return;
	}
	
	// avoid hitting things while sword isn't swinging,
	// avoid hitting yourself, and
	// avoid hitting the same OtherActor twice
	if (Swinging && OtherActor != WeaponHolder &&
		!ThingsHit.Contains(OtherActor))
	{		

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Sword hit something...");
		ARaiderCharacter *avatar = Cast<ARaiderCharacter>(OtherActor);
		if (avatar)
		{
			//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Applying damage to Player..");
			avatar->ApplyDamage(AttackDamage);
		}
		ThingsHit.Add(OtherActor);		
	}
}

void AMeleeWeapon::Swing()
{
	ThingsHit.Empty(); // empty the list
	Swinging = true;
}

void AMeleeWeapon::Rest()
{
	ThingsHit.Empty();
	Swinging = false;
}

// Called when the game starts or when spawned
void AMeleeWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMeleeWeapon::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

