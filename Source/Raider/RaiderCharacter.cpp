// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Raider.h"
#include "RaiderCharacter.h"
#include "GameFramework/PlayerController.h"
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

void ARaiderCharacter::SetupPlayerInputComponent(UInputComponent* InputComponent)
{
	// set up gameplay key bindings
	InputComponent->BindAxis("MoveForward", this, &ARaiderCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ARaiderCharacter::MoveRight);

	InputComponent->BindAction("Fire", IE_Pressed, this, &ARaiderCharacter::OnFire);
}

void ARaiderCharacter::MoveForward(float axisValue)
{
	if ((Controller != NULL) && (axisValue != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, axisValue);
	}
}

void ARaiderCharacter::MoveRight(float axisValue)
{
	if ((Controller != NULL) && (axisValue != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = Controller->GetControlRotation();
		// Limit pitch when walking or falling
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling())
		{
			Rotation.Pitch = 0.0f;
		}
		// add movement in that direction
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, axisValue);
	}
}


void ARaiderCharacter::OnFire()
{
	// Get the coordinates of the mouse from our controller  
	float LocationX;
	float LocationY;
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	PlayerController->GetMousePosition(LocationX, LocationY);
	FVector2D MousePosition(LocationX, LocationY);


	FVector LaunchDir;

	FHitResult Hit;
	//Controller->CastToPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, Hit);
	Controller->CastToPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit){
		if (Hit.Actor != NULL){
			
			LaunchDir = Hit.ImpactPoint;
		}
	}

	// try and fire a projectile
	if (ProjectileClass != NULL)
	{
		// Get the camera transform
		FVector CameraLoc;
		FRotator CameraRot;
		GetActorEyesViewPoint(CameraLoc, CameraRot);
		// MuzzleOffset is in camera space, so transform it to world space before offsetting from the camera to find the final muzzle position
		FVector const MuzzleLocation = CameraLoc + FTransform(CameraRot).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRot;
		MuzzleRotation.Pitch += 0.0f;          // skew the aim upwards a bit
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = Instigator;
			// spawn the projectile at the muzzle
			AProjectile* const Projectile = World->SpawnActor<AProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Projectile)
			{
				// find launch direction
				FVector const LaunchDir = (Hit.ImpactPoint - MuzzleLocation).GetSafeNormal();
				//Projectile->InitVelocity(LaunchDir);
				Projectile->InitVelocity(LaunchDir);
			}
		}
	}
}
