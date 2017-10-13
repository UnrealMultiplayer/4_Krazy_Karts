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

	void ApplyResistance(float DeltaTime);

	void ApplySteering(float DeltaTime);

	void ApplyThrottleAcceleration(float DeltaTime);

	void ApplyVelocityToMovement(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float val);

	void MoveRight(float val);

	// The acceleration of the car with no wind resistance in m/s^2.
	UPROPERTY(EditAnywhere)
	float MaxAcceleration;

	// The deceleration when breaking of the car with no wind resistance in m/s^2.
	UPROPERTY(EditAnywhere)
	float MinBreakingDeceleration;

	// Constant deceleration applied to simulate rolling resistance.
	UPROPERTY(EditAnywhere)
	float RollingResistanceDeceleration;

	// Max speed that can be reached when wind resistance equals forward force, in m/s.
	UPROPERTY(EditAnywhere)
	float TopSpeed;

	// The number of degrees rotated per second at full control throw. degrees/s.
	UPROPERTY(EditAnywhere)
	float FullSteerRate = 45;

	FVector Velocity;
	float WheelThrow;

	float Throttle;
};
