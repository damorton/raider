// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Raider.h"
#include "RaiderCharacter.h"
#include "Projectile.h"

ARaiderCharacter::ARaiderCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->AttachTo(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

}

void ARaiderCharacter::OnFire(FHitResult Hit)
{
	// Try and fire the Projectile
	if (ProjectileClass != NULL)
	{		

		// Get the camera trasnform to set the gun muzzle location
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);

		// Transform MuzzleOffset from Camera Space to World Space before offsetting from the camera
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		//FRotator MuzzleRotation = CameraRot;
		FRotator MuzzleRotation = this->GetActorRotation();
		MuzzleRotation.Pitch += 20.0f;
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;

			// Spawn the projectile at the muzzle position
			AProjectile * const Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// Find launch direction
				//FVector const LaunchDir = MuzzleRotation.Vector();
				//FVector const LaunchDir = Hit.ImpactPoint;

				Projectile->InitVelocity(Hit.ImpactPoint);
				//Projectile->InitVelocity(Hit.ImpactPoint);
			}
		}
	}
}
