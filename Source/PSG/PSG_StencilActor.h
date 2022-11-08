/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description: 
/// Actors that switch the Material of their StaticMeshComponents between translucent and opaque modes in runtime.
/// Intended to be used for Objects that should only be visible behind a panel (stencil mask system), but can then switch to being fully visible without masking. 

#pragma once

#include "CoreMinimal.h"
#include "PSG_FMaterialFlipFlop.h"
#include "GameFramework/Actor.h"
#include "PSG_StencilActor.generated.h"

UCLASS()
class PSG_API APSG_StencilActor : public AActor
{
	GENERATED_BODY()
	
public:	
	APSG_StencilActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	void SetMeshOpaque();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StaticMesh)
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=StaticMesh)
	FMaterialFlipFlop StaticMeshMaterial;
};
