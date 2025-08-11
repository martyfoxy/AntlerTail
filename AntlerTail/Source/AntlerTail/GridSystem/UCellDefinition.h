#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UCellDefinition.generated.h"

class UStaticMesh;
class UMaterialInterface;

UCLASS(BlueprintType)
class UCellDefinition : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
	UStaticMesh* Mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* Material = nullptr;

	UPROPERTY(EditAnywhere)
	FVector MeshOffset = FVector::ZeroVector;

	UPROPERTY(EditAnywhere)
	FRotator MeshRotation = FRotator::ZeroRotator;

	UPROPERTY(EditAnywhere, Category="Gameplay")
	bool bIsWalkable = true;
};
