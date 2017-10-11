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

	void ApplySteering(float DeltaTime);

	void ApplyThrottleAcceleration(float DeltaTime);

	void ApplyVelocityToMovement(float DeltaTime);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	void MoveForward(float val);

	void MoveRight(float val);

	UPROPERTY(EditAnywhere)
	float Acceleration;

	UPROPERTY(EditAnywhere)
	float TopSpeed;

	UPROPERTY(EditAnywhere)
	float FullSteerDegrees = 45;

	FVector Velocity;
	float WheelThrow;

	float Throttle;
};
