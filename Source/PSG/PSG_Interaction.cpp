// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#include "PSG_Interaction.h"


APSG_Interaction::APSG_Interaction()
{
	overlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	overlapComponent->InitBoxExtent(FVector(150.f));
}


void APSG_Interaction::BeginPlay()
{
	Super::BeginPlay();

	overlapComponent->OnComponentBeginOverlap.AddDynamic(this, &APSG_Interaction::OnBoxBeginOverlap);
	overlapComponent->OnComponentEndOverlap.AddDynamic(this, &APSG_Interaction::OnBoxEndOverlap);
}

void APSG_Interaction::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APSG_Character* Character = Cast<APSG_Character>(OtherActor);
	if(Character != nullptr)
	{
		if(OtherComp == OtherActor->GetRootComponent())
			Character->OnInteraction.AddDynamic(this, &APSG_Interaction::OnInteraction);
	}
}

void APSG_Interaction::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APSG_Character* Character = Cast<APSG_Character>(OtherActor);
	if(Character != nullptr)
	{
		if(OtherComp == OtherActor->GetRootComponent())
			Character->OnInteraction.RemoveDynamic(this, &APSG_Interaction::OnInteraction);
	}
}

void APSG_Interaction::OnInteraction_Implementation() {}