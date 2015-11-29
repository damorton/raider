// Fill out your copyright notice in the Description page of Project Settings.

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

	m_Health = 10;
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
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, "Applying damage to door");

	m_Health -= damage;
	if (m_Health <= 0)
	{
		Destroy();
	}
}



