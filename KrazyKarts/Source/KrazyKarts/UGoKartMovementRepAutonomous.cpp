// Fill out your copyright notice in the Description page of Project Settings.

#include "UGoKartMovementRepAutonomous.h"
#include "GameFramework/Actor.h"
#include "GoKartMovementReplicator.h"

// Sets default values for this component's properties
UUGoKartMovementRepAutonomous::UUGoKartMovementRepAutonomous()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UUGoKartMovementRepAutonomous::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUGoKartMovementRepAutonomous::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto MovementComponent = GetOwner()->FindComponentByClass<UGoKartMovementComponent>();
	if (MovementComponent == nullptr) return;
	FGoKartMove LastMove = MovementComponent->GetLastMove();

	Replicator->Server_SendMove(LastMove);

	UnacknowledgedMoves.Add(LastMove);

	UE_LOG(LogTemp, Warning, TEXT("Queue length: %d"), UnacknowledgedMoves.Num());
}

void UUGoKartMovementRepAutonomous::ReplicatedState(FGoKartState ServerState)
{
	auto MovementComponent = GetOwner()->FindComponentByClass<UGoKartMovementComponent>();
	if (MovementComponent == nullptr) return;

	GetOwner()->SetActorTransform(ServerState.Tranform);
	MovementComponent->SetVelocity(ServerState.Velocity);

	ClearAcknowledgeMoves(ServerState.LastMove);

	for (const FGoKartMove& Move : UnacknowledgedMoves)
	{
		MovementComponent->SimulateMove(Move);
	}
}

void UUGoKartMovementRepAutonomous::ClearAcknowledgeMoves(FGoKartMove LastMove)
{
	TArray<FGoKartMove> NewMoves;

	for (const FGoKartMove& Move : UnacknowledgedMoves)
	{
		if (Move.Time > LastMove.Time)
		{
			NewMoves.Add(Move);
		}
	}

	UnacknowledgedMoves = NewMoves;
}


