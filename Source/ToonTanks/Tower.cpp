// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"

void ATower::BeginPlay()
{
	Super::BeginPlay();
    StartRotation = GetActorRotation();
    PlayerControllerRef = GetWorld()->GetFirstPlayerController();
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    FVector TowerLocation = GetActorLocation();

    if (PlayerControllerRef)
    {
        ABasePawn* TankPawn = Cast<ABasePawn>(PlayerControllerRef->GetPawn());

        if (TankPawn)
        {
            APawn* PlayerPawn = PlayerControllerRef->GetPawn();

            if(PlayerPawn)
            {
                float Distance = (TowerLocation - PlayerPawn->GetActorLocation()).Size();
                
                if (Distance <= DetectionRadius)
                {
                    // Start the firing timer only if it's not already active
                    if (!GetWorldTimerManager().IsTimerActive(FiringTimerHandle))
                    {
                        GetWorldTimerManager().SetTimer(FiringTimerHandle, this, &ATower::Fire, 2.0f, true);
                    }
                    RotateTurret(PlayerPawn->GetActorLocation(), DeltaTime);
                }
                else
                {
                    // Stop the firing timer if it's active
                    GetWorldTimerManager().ClearTimer(FiringTimerHandle);

                    TurretMesh->SetWorldRotation(FMath::Lerp(TurretMesh->GetComponentRotation(), StartRotation, LerpAlpha * DeltaTime));
                }
            }
        }
    }

}
