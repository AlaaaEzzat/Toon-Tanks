// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "HealthComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileBody"));
    RootComponent = BaseMesh;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	BaseMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnProjectileHit);
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
    {
        // Get a reference to the UHealthComponent attached to the OtherActor
        UHealthComponent* HealthComponent = OtherActor->FindComponentByClass<UHealthComponent>();
        UGameplayStatics::SpawnEmitterAtLocation(this , hitEffect , OtherActor->GetActorLocation() , OtherActor->GetActorRotation());
        // Check if the HealthComponent is valid
        if (HealthComponent)
        {
            // Call the TakeDamage function of the HealthComponent, passing the BaseDamage
            HealthComponent->OnTakeDamage(BaseDamage);
        }
        
        UE_LOG(LogTemp, Warning, TEXT("Projectile hit: %s"), *OtherActor->GetName());
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Projectile hit something!"));
    }
	Destroy();
}

