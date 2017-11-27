// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoKartMovementComponent.h"
#include "GoKartMovementReplicator.h"
#include "UGoKartMovementRepAutonomous.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KRAZYKARTS_API UUGoKartMovementRepAutonomous : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UUGoKartMovementRepAutonomous();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetReplicator(UGoKartMovementReplicator* Ptr) { Replicator = Ptr; };

	void ReplicatedState(FGoKartState State);

private:
	void ClearAcknowledgeMoves(FGoKartMove LastMove);

	TArray<FGoKartMove> UnacknowledgedMoves;

	UGoKartMovementReplicator* Replicator;
	
};
