// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("rootCapsuleBody"));
    BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TankBody"));
    RootComponent=CapsuleComponent;
    BaseMesh->SetupAttachment(CapsuleComponent);
    TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretBody"));
    TurretMesh->SetupAttachment(BaseMesh);
    ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Object"));
    ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

// Called when the game starts or when spawned
void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePawn::RotateTurret(FVector LookAtTarger , float DeltaTime)
{
    FVector ToTarget = LookAtTarger - TurretMesh->GetComponentLocation();
    FRotator LookAtRotation = ToTarget.Rotation();
    LookAtRotation.Roll = LookAtRotation.Pitch = 0;

    TurretMesh->SetWorldRotation(FMath::Lerp(TurretMesh->GetComponentRotation(), LookAtRotation, LerpAlpha * DeltaTime));
}

void ABasePawn::Fire()
{
    if (ProjectileClass)
    {
        FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
        FRotator SpawnRotation = ProjectileSpawnPoint->GetComponentRotation();
        AProjectile* SpawnedProjectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, SpawnLocation, SpawnRotation);
        UE_LOG(LogTemp, Log, TEXT("Projectile fired!"));

    }
}



