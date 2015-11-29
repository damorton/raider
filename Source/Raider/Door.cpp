//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#include "Raider.h"
#include "Door.h"
#include "Engine.h"

ADoor::ADoor()
{
	PrimaryActorTick.bCanEverTick = true;
	m_CollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Door Collision Component"));
	RootComponent = m_CollisionComponent;

	m_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door Mesh"));
	m_Mesh->AttachTo(RootComponent);

	m_Health = 100;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADoor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ADoor::applyDamage(float damage)
{
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Applying damage to door");
	
	if (m_HitParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, m_HitParticle, GetActorLocation());
	}

	m_Health -= damage;
	if (m_Health <= 0)
	{
		// Try and play the sound if specified
		if (m_DestructionSound != NULL)
		{
			UGameplayStatics::PlaySoundAtLocation(this, m_DestructionSound, GetActorLocation());
		}
		Destroy();
	}
}



