// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GoKart.generated.h"

UCLASS()
class KRAZYKARTS_API AGoKart : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGoKart();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetResistance();

	void ApplySteering(float DeltaTime);

	FVector GetDriveForce();

	float GetSteeringRate();

	void UpdatePositionWithVelocity(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float val);

	void MoveRight(float val);

	// Force of engine in N.
	UPROPERTY(EditAnywhere)
	float DriveForce;

	// Mass of the car in kg.
	UPROPERTY(EditAnywhere)
	float Mass;

	// Force when breaking in N.
	UPROPERTY(EditAnywhere)
	float BreakingForce;

	// Force required to start moving in N.
	UPROPERTY(EditAnywhere)
	float RollingResistance;

	// How much drag affects the car (unitless).
	UPROPERTY(EditAnywhere)
	float DragCoefficient;

	// The number of degrees rotated per second at full control throw. degrees/s.
	UPROPERTY(EditAnywhere)
	float FullSteerRate = 45;

	// Minimum forward speed at which to allow steering (m/s).
	UPROPERTY(EditAnywhere)
	float MinSteeringSpeed = 1;

	FVector Velocity;
	float WheelThrow;

	float Throttle;
};
