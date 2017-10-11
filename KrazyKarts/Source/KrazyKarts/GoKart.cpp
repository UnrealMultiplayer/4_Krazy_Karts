// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKart.h"

#include "Components/InputComponent.h"

// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ApplyThrottleAcceleration(DeltaTime);

	ApplyVelocityToMovement(DeltaTime);
}

void AGoKart::ApplyThrottleAcceleration(float DeltaTime)
{
	FVector AccelerationVector = GetActorForwardVector() * Throttle * Acceleration * DeltaTime;

	Velocity += AccelerationVector;
}

void AGoKart::ApplyVelocityToMovement(float DeltaTime)
{
	FVector Delta = Velocity * DeltaTime;
	FHitResult Hit(1);
	AddActorWorldOffset(Delta, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		Delta = FVector::VectorPlaneProject(Delta * (1 - Hit.Time), Hit.Normal);
		Velocity = FVector::VectorPlaneProject(Velocity, Hit.Normal);

		AddActorWorldOffset(Delta, true);
	}
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
}

void AGoKart::MoveForward(float val)
{
	Throttle = val;
}


