#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitGridAgentComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANTLERTAIL_API UUnitGridAgentComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUnitGridAgentComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
