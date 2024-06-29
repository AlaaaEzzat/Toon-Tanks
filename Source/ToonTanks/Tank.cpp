// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"

void ATank::BeginPlay()
{
	Super::BeginPlay();
    PlayerControllerRef = Cast<APlayerController>(GetController());
	
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    if(PlayerControllerRef != nullptr)
    {
        FHitResult HitResult;
        bool BHitSomething = PlayerControllerRef->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility , false , HitResult);

        if(BHitSomething == true){
            DrawDebugSphere(GetWorld() , HitResult.ImpactPoint , 10 , 15 , FColor::Red);
            RotateTurret(HitResult.ImpactPoint , DeltaTime);
        }    
    }

}

ATank::ATank()
{
    springArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
    springArmComponent -> SetupAttachment(RootComponent);

    SpringArmCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
    SpringArmCamera -> SetupAttachment(springArmComponent);
}

void ATank::Move(float Value)
{
    if(CanSprint == true)
    {
        FVector DeltaMovement(Value * Speed * SprintSpeed * GetWorld()->GetDeltaSeconds() , 0 , 0);
        AddActorLocalOffset(DeltaMovement , true);
    }
    else
    {
        FVector DeltaMovement(Value * Speed * GetWorld()->GetDeltaSeconds() , 0 , 0);
        AddActorLocalOffset(DeltaMovement , true);
    }
    
}
void ATank::Turn(float Value)
{
    FRotator DeltaRotation(0 , Value * RotationSpeed * GetWorld()->GetDeltaSeconds() , 0);
    AddActorLocalRotation(DeltaRotation);
}

void ATank::FireBullets()
{
    Fire();
}

void ATank::Sprint(float Value)
{
    if(Value > 0)
    {
        CanSprint = true;
    }
    else
    {
        CanSprint = false;
    }
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent -> BindAxis(TEXT("MoveForward") , this , &ATank::Move);
    PlayerInputComponent -> BindAxis(TEXT("Turn") , this , &ATank::Turn);
    PlayerInputComponent -> BindAxis(TEXT("Sprint") , this , &ATank::Sprint);
    PlayerInputComponent -> BindAction(TEXT("Fire"), IE_Pressed , this, &ATank::FireBullets);

}
