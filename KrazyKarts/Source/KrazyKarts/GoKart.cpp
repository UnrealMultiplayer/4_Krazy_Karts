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

	FVector Forces; 
	Forces += GetResistance();
	
	Forces += GetDriveForce();

	Velocity += (Forces / Mass) * DeltaTime;

	ApplySteering(DeltaTime);

	UpdatePositionWithVelocity(DeltaTime);
}

FVector AGoKart::GetResistance()
{
	FVector Force = - Velocity.GetSafeNormal() * Velocity.SizeSquared() * DragCoefficient;

	Force -= Velocity.GetSafeNormal() * RollingResistance;

	return Force;
}

void AGoKart::ApplySteering(float DeltaTime)
{
	FQuat Rotation(GetActorUpVector(), GetSteeringRate() * DeltaTime);
	Velocity = Rotation.RotateVector(Velocity);

	AddActorWorldRotation(Rotation);
}

float AGoKart::GetSteeringRate()
{
	float RotationAngle = FMath::DegreesToRadians(FullSteerRate) * WheelThrow;
	float ForwardSpeed = FVector::DotProduct(GetActorForwardVector(), Velocity);
	if (ForwardSpeed > MinSteeringSpeed)
	{
		return RotationAngle;
	}
	if (ForwardSpeed < -MinSteeringSpeed)
	{
		return -RotationAngle;
	}
	return 0;
}

FVector AGoKart::GetDriveForce()
{
	FVector Force = GetActorForwardVector() * Throttle;

	if (FVector::DotProduct(Velocity, Force) < 0)
	{
		Force *= BreakingForce;
	}
	else 
	{
		Force *= DriveForce;
	}

	return Force;
}

void AGoKart::UpdatePositionWithVelocity(float DeltaTime)
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


