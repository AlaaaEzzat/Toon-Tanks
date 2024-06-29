// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


class UParticleSystemComponent;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOONTANKS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	void OnTakeDamage(int Damage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere , BlueprintReadOnly , Category = "Properties")
	float CurrentHealth;

	UPROPERTY(EditAnywhere , Category = "Effect")
	UParticleSystem* DeathEffect;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly , Category = "Properties")
	float MaxHealth;
};
