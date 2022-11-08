// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#include "PSG_StencilActor.h"

APSG_StencilActor::APSG_StencilActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APSG_StencilActor::BeginPlay()
{
	Super::BeginPlay();
	StaticMeshComp->SetMaterial(StaticMeshMaterial.materialID, StaticMeshMaterial.translucentMaterial);
}

void APSG_StencilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APSG_StencilActor::SetMeshOpaque()
{
	StaticMeshComp->SetMaterial(StaticMeshMaterial.materialID, StaticMeshMaterial.opaqueMaterial);
}

