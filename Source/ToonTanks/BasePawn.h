// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class USceneComponent;
UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void RotateTurret(FVector LookAtTarget , float DeltaTime);

	void Fire();
	
	UPROPERTY(EditAnywhere)
    UCapsuleComponent * CapsuleComponent;
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent * BaseMesh;
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent * TurretMesh;
    UPROPERTY(EditAnywhere)
    USceneComponent * ProjectileSpawnPoint;
	UPROPERTY(EditAnywhere)
	float LerpAlpha = 0.5f;

	UPROPERTY(EditAnywhere , Category = "Effect")
	UParticleSystem* hitEffect;
	

	UPROPERTY(EditDefaultsOnly, Category = "Projectile")
	TSubclassOf<AProjectile> ProjectileClass;

};
