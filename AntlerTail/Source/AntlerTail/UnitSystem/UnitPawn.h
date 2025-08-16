#pragma once

#include "CoreMinimal.h"
#include "UnitActionsComponent.h"
#include "UnitGridAgentComponent.h"
#include "UnitMovementComponent.h"
#include "GameFramework/Pawn.h"
#include "UnitPawn.generated.h"

UCLASS()
class ANTLERTAIL_API AUnitPawn : public APawn
{
	GENERATED_BODY()

public:
	AUnitPawn();

	UPROPERTY(EditAnywhere)
	UUnitGridAgentComponent* UnitGridAgent;

	UPROPERTY(EditAnywhere)
	UUnitMovementComponent* UnitMovementComponent;

	UPROPERTY(EditAnywhere)
	UUnitActionsComponent* UnitActionsComponent;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
