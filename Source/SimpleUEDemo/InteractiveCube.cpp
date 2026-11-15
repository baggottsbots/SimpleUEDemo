#include "InteractiveCube.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Engine.h"
#include "Materials/MaterialInstanceDynamic.h"

AInteractiveCube::AInteractiveCube()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	if (CubeMesh.Succeeded())
	{
		MeshComponent->SetStaticMesh(CubeMesh.Object);
	}

	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetGenerateOverlapEvents(true);
	MeshComponent->OnComponentBeginOverlap.AddDynamic(this, &AInteractiveCube::OnOverlapBegin);
}

void AInteractiveCube::BeginPlay()
{
	Super::BeginPlay();

	// Set initial red color
	UMaterialInstanceDynamic* DynMaterial = MeshComponent->CreateDynamicMaterialInstance(0);
	if (DynMaterial)
	{
		DynMaterial->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor::Red);
	}
}

void AInteractiveCube::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bCollected || !OtherActor || OtherActor == this) return;

	// Simple check if it's a pawn (player)
	if (OtherActor->IsA(APawn::StaticClass()))
	{
		bCollected = true;
		UMaterialInstanceDynamic* DynMaterial = MeshComponent->CreateDynamicMaterialInstance(0);
		if (DynMaterial)
		{
			DynMaterial->SetVectorParameterValue(TEXT("BaseColor"), FLinearColor::Green);
		}
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Cube Collected! Score +1"));
	}
}
