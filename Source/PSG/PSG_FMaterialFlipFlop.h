/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Enables Actors (PSG_StencilActor) to switch the Material of their StaticMeshComponents between translucent and opaque modes in runtime.
/// Intended to be used for Objects that should only be visible behind a panel (stencil mask system), but can then switch to being fully visible without masking. 

#pragma once

#include "CoreMinimal.h"
#include "PSG_FMaterialFlipFlop.generated.h"

USTRUCT(BlueprintType)
struct FMaterialFlipFlop
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		int materialID = 0;

	UPROPERTY(BlueprintReadWrite)
		UMaterial* translucentMaterial;

	UPROPERTY(BlueprintReadWrite)
		UMaterial* opaqueMaterial;

	FMaterialFlipFlop() = default;
};
