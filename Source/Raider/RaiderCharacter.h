// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "RaiderCharacter.generated.h"

UCLASS(Blueprintable)
class ARaiderCharacter : public ACharacter
{
	//GENERATED_BODY()
	GENERATED_UCLASS_BODY()

public:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION()
	void MoveForward(float axisValue);

	UFUNCTION()
	void MoveRight(float axisValue);

	//handles firing
	UFUNCTION()
	void OnFire();

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	// Gun muzzle's offset from the player
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;

	// Projectile class used to shoot at enemies
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectile> ProjectileClass;

	// Players current health point value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float Hp;

	// Players  maximum health points value
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerProperties)
	float MaxHp;

	virtual void Tick(float DeltaSeconds) override;

	// Apply damage to the player character
	void ApplyDamage(float damage);
};