// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKart.h"

#include "Components/InputComponent.h"

const float METERS_TO_UNREAL = 100;

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

	ApplyResistance(DeltaTime);

	ApplyThrottleAcceleration(DeltaTime);

	ApplySteering(DeltaTime);

	ApplyVelocityToMovement(DeltaTime);
}

void AGoKart::ApplyResistance(float DeltaTime)
{
	float DecelerationDueToResistance = MaxAcceleration * ( Velocity.SizeSquared() / FMath::Square(TopSpeed) );
	Velocity -= Velocity.GetSafeNormal() * DecelerationDueToResistance * DeltaTime ;

	Velocity = Velocity.GetSafeNormal() * FMath::Clamp(Velocity.Size() - RollingResistanceDeceleration * DeltaTime, 0.f, Velocity.Size());
}

void AGoKart::ApplySteering(float DeltaTime)
{
	float RotationAngle = FMath::DegreesToRadians(FullSteerRate) * WheelThrow * DeltaTime;
	if (FVector::DotProduct(GetActorForwardVector(), Velocity) < 0)
	{
		RotationAngle = -RotationAngle;
	}
	FQuat Rotation(GetActorUpVector(), RotationAngle);
	Velocity = Rotation.RotateVector(Velocity);

	AddActorWorldRotation(Rotation);
}

void AGoKart::ApplyThrottleAcceleration(float DeltaTime)
{
	FVector AccelerationVector = GetActorForwardVector() * Throttle * DeltaTime;

	if (FVector::DotProduct(Velocity, AccelerationVector) < 0) 
	{
		AccelerationVector *= MinBreakingDeceleration;
	}
	else 
	{
		AccelerationVector *= MaxAcceleration;
	}

	Velocity += AccelerationVector;
}

void AGoKart::ApplyVelocityToMovement(float DeltaTime)
{
	FVector Delta = Velocity * METERS_TO_UNREAL * DeltaTime;
	FHitResult Hit(1);
	AddActorWorldOffset(Delta, true, &Hit);

	if (Hit.IsValidBlockingHit())
	{
		Velocity = FVector::ZeroVector;
	}
}

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);
}

void AGoKart::MoveForward(float val)
{
	Throttle = val;
}

void AGoKart::MoveRight(float val)
{
	WheelThrow = val;
}


