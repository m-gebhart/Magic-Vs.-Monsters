// Copyright Epic Games, Inc. All Rights Reserved.

#include "PSG_PickUpComponent.h"

UPSG_PickUpComponent::UPSG_PickUpComponent()
{
	SphereRadius = 32.f;
}

void UPSG_PickUpComponent::BeginPlay()
{
	Super::BeginPlay();

	OnComponentBeginOverlap.AddDynamic(this, &UPSG_PickUpComponent::OnSphereBeginOverlap);
}

void UPSG_PickUpComponent::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APSG_Character* character = dynamic_cast<APSG_Character*>(OtherActor);
	if(character != nullptr)
	{
		OnPickUp.Broadcast(character);
		OnComponentBeginOverlap.RemoveAll(this);
	}
}
