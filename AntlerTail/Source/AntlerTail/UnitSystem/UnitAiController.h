#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "UnitAiController.generated.h"

UCLASS()
class ANTLERTAIL_API AUnitAiController : public AAIController
{
	GENERATED_BODY()

public:
	AUnitAiController();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
