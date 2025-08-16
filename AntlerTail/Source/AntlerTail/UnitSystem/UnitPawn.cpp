#include "UnitPawn.h"

AUnitPawn::AUnitPawn()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnitPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AUnitPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

