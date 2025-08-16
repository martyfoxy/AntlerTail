#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UnitActionsComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ANTLERTAIL_API UUnitActionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UUnitActionsComponent();

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
