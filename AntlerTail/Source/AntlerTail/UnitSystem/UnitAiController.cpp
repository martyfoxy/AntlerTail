#include "UnitAiController.h"

AUnitAiController::AUnitAiController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AUnitAiController::BeginPlay()
{
	Super::BeginPlay();
	
}

void AUnitAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

