#include "GridMapActor.h"

#include "Components/HierarchicalInstancedStaticMeshComponent.h"


AGridMapActor::AGridMapActor()
{
	Data = CreateDefaultSubobject<UGridMapData>(TEXT("GridData"));

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;
	
	PreviewMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Preview"));
	PreviewMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	PreviewMesh->SetCastShadow(false);
	PreviewMesh->bHiddenInGame=true;
	PreviewMesh->SetupAttachment(SceneRoot);
	PreviewMesh->SetMobility(EComponentMobility::Movable);
}

void AGridMapActor::EnsureHISMForTypeId(int32 TypeId)
{
	if (HISMByType.Contains(TypeId)) return;

	auto* H = NewObject<UHierarchicalInstancedStaticMeshComponent>(this);
	H->RegisterComponent();
	H->AttachToComponent(SceneRoot, FAttachmentTransformRules::KeepRelativeTransform);
	H->SetMobility(EComponentMobility::Movable);
	if (CellDefinitions.IsValidIndex(TypeId))
	{
		UCellDefinition* CellDefinition = CellDefinitions[TypeId];
		H->SetStaticMesh(CellDefinition->Mesh);
		H->SetMaterial(0, CellDefinition->Material);
	}
	
	HISMByType.Add(TypeId, H);
}

void AGridMapActor::RebuildAllHISMs()
{
	UWorld* World = GetWorld();
	if (!IsValid(World)) return;
	
	if (!GetRootComponent())
	{
		SceneRoot = NewObject<USceneComponent>(this, TEXT("Root"));
		SetRootComponent(SceneRoot);
		SceneRoot->RegisterComponentWithWorld(World);
	}
	
	for (auto& Kv : HISMByType)
	{
		if (Kv.Value)
		{
			Kv.Value->ClearInstances();
			Kv.Value->DestroyComponent();
		}
	}
	HISMByType.Empty();
	
	const int32 Types = CellDefinitions.Num();
	for (int32 i = 0; i < Types; ++i)
	{
		EnsureHISMForTypeId(i);
	}

	if (Data)
	{
		for (const FCellData& C : Data->Cells)
		{
			if (UHierarchicalInstancedStaticMeshComponent** PH = HISMByType.Find(C.TypeId))
			{
				(*PH)->AddInstance(FTransform(C.Rotation, GridToWorld(C.Position)));
			}
		}
	}
}

#if WITH_EDITOR
#include "UObject/UObjectGlobals.h"
void AGridMapActor::PostLoad()
{
	Super::PostLoad();
	RebuildAllHISMs();
}

void AGridMapActor::OnConstruction(const FTransform& Xform)
{
	Super::OnConstruction(Xform);
	RebuildAllHISMs();
}

void AGridMapActor::PostEditUndo()
{
	Super::PostEditUndo();
	RebuildAllHISMs();
}

void AGridMapActor::PostEditChangeProperty(FPropertyChangedEvent& E)
{
	Super::PostEditChangeProperty(E);
	const FName Name = E.Property ? E.Property->GetFName() : NAME_None;
	
	if (Name == GET_MEMBER_NAME_CHECKED(AGridMapActor, CellDefinitions))
	{
		RebuildAllHISMs();
	}
}

void AGridMapActor::PostInitProperties()
{
	Super::PostInitProperties();
	if (GIsEditor)
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &AGridMapActor::OnAnyObjectPropertyChanged);
	}
}

void AGridMapActor::BeginDestroy()
{
	if (GIsEditor)
	{
		FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
	}
	Super::BeginDestroy();
}

void AGridMapActor::OnAnyObjectPropertyChanged(UObject* Obj, FPropertyChangedEvent& E)
{
	if (CellDefinitions.Contains(Cast<UCellDefinition>(Obj)))
	{
		RebuildAllHISMs();
	}
}
#endif

