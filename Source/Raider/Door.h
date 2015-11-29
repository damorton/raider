//
// Raider 2015
//
// 3D Tower Defense Game 
//
// Author: David Morton
// Date: November 2015
//
#pragma once

#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class RAIDER_API ADoor : public AActor
{
	//GENERATED_UCLASS_BODY()
	GENERATED_BODY()
	
public:	
	ADoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = Door)
	void applyDamage(float damage);

	float m_Health;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Door)
	UBoxComponent *m_CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Door)
	UStaticMeshComponent *m_Mesh;	

	// Sound for door destruction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	class USoundBase* m_DestructionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UParticleSystem *m_HitParticle;
};
