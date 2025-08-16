#include "UnitActionsComponent.h"


UUnitActionsComponent::UUnitActionsComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUnitActionsComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UUnitActionsComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

