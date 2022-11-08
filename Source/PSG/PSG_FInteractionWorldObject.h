/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
/// 
/// Description:
/// Enables Actors (PSG_StencilActor) to switch the Material of their StaticMeshComponents between translucent and opaque modes in runtime.
/// Intended to be used for Objects that should only be visible behind a panel (stencil mask system), but can then switch to being fully visible without masking. 

#pragma once

#include "CoreMinimal.h"
#include "PSG_FInteractionWorldObject.generated.h"

USTRUCT(BlueprintType)
struct FInteractionWorldObject
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
		bool bInteractable = true;

	UPROPERTY(BlueprintReadWrite)
		FVector originLocation;

	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* meshComponent;

	FInteractionWorldObject() = default;
};
