// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

	public:

	ATank();

	void Move(float v);

	void Turn(float v);

	void Sprint(float v);

	void FireBullets();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

	protected:
		// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	private:


	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComponent; 

	UPROPERTY(EditAnywhere)
	class UCameraComponent* SpringArmCamera;

	UPROPERTY(EditAnywhere)
	float Speed = 30;

	UPROPERTY(EditAnywhere)
	float SprintSpeed = 30;

	UPROPERTY(EditAnywhere)
	float RotationSpeed = 30;

	UPROPERTY(EditAnywhere)
	bool CanSprint;

	UPROPERTY(VisibleAnywhere)
	class APlayerController* PlayerControllerRef;



	
};
