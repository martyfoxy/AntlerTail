#include "UnitGridAgentComponent.h"

UUnitGridAgentComponent::UUnitGridAgentComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UUnitGridAgentComponent::BeginPlay()
{
	Super::BeginPlay();	
}

void UUnitGridAgentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                            FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

