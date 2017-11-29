// Fill out your copyright notice in the Description page of Project Settings.

#include "GoKart.h"

#include "Components/InputComponent.h"

#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "UnrealNetwork.h"

// Sets default values
AGoKart::AGoKart()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	MovementComponent = CreateDefaultSubobject<UGoKartMovementComponent>(TEXT("MovementComponent"));
}

// Called when the game starts or when spawned
void AGoKart::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		NetUpdateFrequency = 1;
	}
}

void AGoKart::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGoKart, ServerState);
}

FString GetEnumText(ENetRole Role)
{
	switch (Role)
	{
	case ROLE_None:
		return "None";
	case ROLE_SimulatedProxy:
		return "SimulatedProxy";
	case ROLE_AutonomousProxy:
		return "AutonomousProxy";
	case ROLE_Authority:
		return "Authority";
	default:
		return "ERROR";
	}
}

// Called every frame
void AGoKart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MovementComponent == nullptr) return;

	if (Role == ROLE_AutonomousProxy)
	{
		FGoKartMove Move = MovementComponent->CreateMove(DeltaTime);
		MovementComponent->SimulateMove(Move);

		UnacknowledgedMoves.Add(Move);
		Server_SendMove(Move);
	}

	// We are the server and in control of the pawn.
	if (Role == ROLE_Authority && GetRemoteRole() == ROLE_SimulatedProxy)
	{
		FGoKartMove Move = MovementComponent->CreateMove(DeltaTime);
		Server_SendMove(Move);
	}

	if (Role == ROLE_SimulatedProxy)
	{
		MovementComponent->SimulateMove(ServerState.LastMove);
	}

	DrawDebugString(GetWorld(), FVector(0, 0, 100), GetEnumText(Role), this, FColor::White, DeltaTime);
}

void AGoKart::OnRep_ServerState()
{
	if (MovementComponent == nullptr) return;

	SetActorTransform(ServerState.Tranform);
	MovementComponent->SetVelocity(ServerState.Velocity);

	ClearAcknowledgeMoves(ServerState.LastMove);

	for (const FGoKartMove& Move : UnacknowledgedMoves)
	{
		MovementComponent->SimulateMove(Move);
	}
}

void AGoKart::ClearAcknowledgeMoves(FGoKartMove LastMove)
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

// Called to bind functionality to input
void AGoKart::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AGoKart::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AGoKart::MoveRight);

}

void AGoKart::MoveForward(float Value)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SetThrottle(Value);
}


void AGoKart::MoveRight(float Value)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SetSteeringThrow(Value);
}

void AGoKart::Server_SendMove_Implementation(FGoKartMove Move)
{
	if (MovementComponent == nullptr) return;

	MovementComponent->SimulateMove(Move);

	ServerState.LastMove = Move;
	ServerState.Tranform = GetActorTransform();
	ServerState.Velocity = MovementComponent->GetVelocity();
}

bool AGoKart::Server_SendMove_Validate(FGoKartMove Move)
{
	return true; //TODO: Make better validation
}