//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#include "Raider.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Door.h"
#include "Monster.h"
#include "Engine.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

AProjectile::AProjectile(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CollisionComp = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("SphereComponent"));
	CollisionComp->InitSphereRadius(15.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);

	RootComponent = CollisionComp;

	ProjectileMovement = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 3000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.3f;


	m_ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particles"));
	m_ParticleSystem->bAutoActivate = true;
	m_ParticleSystem->AttachTo(RootComponent);

	// Life span of projectile object
	InitialLifeSpan = 3.0f;

	// Damage value applied to objects hit
	m_fDamage = 10.0f;
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AProjectile::InitVelocity(const FVector& ShootDirection)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
	}
}

void AProjectile::OnHit(AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, "Hit something...");
		OtherComp->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);

		// Apply damage to doors
		if (OtherActor->IsA(ADoor::StaticClass()))
		{
			ADoor *door = Cast<ADoor>(OtherActor);
			door->applyDamage(m_fDamage);
		}		

		// Apply damage to enemies
		if (OtherActor->IsA(AMonster::StaticClass()))
		{
			AMonster *monster = Cast<AMonster>(OtherActor);
			monster->applyDamage(m_fDamage);
		}
	}
}