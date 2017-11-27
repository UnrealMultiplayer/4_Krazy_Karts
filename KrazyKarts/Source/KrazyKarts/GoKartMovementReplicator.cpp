// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKartMovementReplicator.h"
#include "UnrealNetwork.h"
#include "GameFramework/Actor.h"
#include "UGoKartMovementRepAutonomous.h"

// Sets default values for this component's properties
UGoKartMovementReplicator::UGoKartMovementReplicator()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);

	// ...
}


// Called when the game starts
void UGoKartMovementReplicator::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwnerRole() == ROLE_AutonomousProxy)
	{
		auto createdComp = NewObject<UUGoKartMovementRepAutonomous>(GetOwner());
		if (createdComp)
		{
			createdComp->RegisterComponent();
			createdComp->SetReplicator(this);
		}
	}
}


// Called every frame
void UGoKartMovementReplicator::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto MovementComponent = GetOwner()->FindComponentByClass<UGoKartMovementComponent>();
	if (MovementComponent == nullptr) return;
	
	FGoKartMove LastMove = MovementComponent->GetLastMove();

	if (GetOwner()->GetRemoteRole() == ROLE_SimulatedProxy)
	{
		UpdateServerState(LastMove);
	}

	if (GetOwnerRole() == ROLE_SimulatedProxy)
	{
		MovementComponent->SimulateMove(ServerState.LastMove);
	}
}

void UGoKartMovementReplicator::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UGoKartMovementReplicator, ServerState);
}

void UGoKartMovementReplicator::OnRep_ServerState()
{
	auto AutonomousReplicator = GetOwner()->FindComponentByClass<UUGoKartMovementRepAutonomous>();
	if (AutonomousReplicator != nullptr)
	{
		AutonomousReplicator->ReplicatedState(ServerState);

	}
}

void UGoKartMovementReplicator::Server_SendMove_Implementation(FGoKartMove Move)
{
	auto MovementComponent = GetOwner()->FindComponentByClass<UGoKartMovementComponent>();
	if (MovementComponent == nullptr) return;

	MovementComponent->SimulateMove(Move);
	UpdateServerState(Move);
}

void UGoKartMovementReplicator::UpdateServerState(FGoKartMove LastMove)
{
	auto MovementComponent = GetOwner()->FindComponentByClass<UGoKartMovementComponent>();
	if (MovementComponent == nullptr) return;

	ServerState.LastMove = LastMove;
	ServerState.Tranform = GetOwner()->GetActorTransform();
	ServerState.Velocity = MovementComponent->GetVelocity();

}

bool UGoKartMovementReplicator::Server_SendMove_Validate(FGoKartMove Move)
{
	return true; //TODO: Make better validation
}