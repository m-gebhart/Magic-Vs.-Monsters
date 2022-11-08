// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#include "PSG_LightToggle.h"
#include "PSG_Character.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"

APSG_LightToggle::APSG_LightToggle()
{
	overlapComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	overlapComponent->InitBoxExtent(FVector(150.f));
}

void APSG_LightToggle::BeginPlay()
{
	Super::BeginPlay();
	overlapComponent->OnComponentBeginOverlap.AddDynamic(this, &APSG_LightToggle::OnBoxBeginOverlap);
	overlapComponent->OnComponentEndOverlap.AddDynamic(this, &APSG_LightToggle::OnBoxEndOverlap);
	
	if (lightActor != nullptr && lightActor->FindComponentByClass<ULightComponent>() != nullptr)
		lightComp = lightActor->FindComponentByClass<ULightComponent>();
}

void APSG_LightToggle::SwitchLight()
{
	if (lightComp != nullptr)
		lightComp->SetVisibility(!IsEnabled());
}

bool APSG_LightToggle::IsEnabled()
{
	if (lightComp != nullptr)
		return lightComp->IsVisible();
	return false;
}

void APSG_LightToggle::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APSG_Character* character = Cast<APSG_Character>(OtherActor);
	if (character != nullptr)
	{
		if(OtherComp == OtherActor->GetRootComponent())
			character->OnInteraction.AddDynamic(this, &APSG_LightToggle::SwitchLight);
	}
}

void APSG_LightToggle::OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	APSG_Character* character = Cast<APSG_Character>(OtherActor);
	if (character != nullptr)
	{
		if(OtherComp == OtherActor->GetRootComponent())
			character->OnInteraction.RemoveDynamic(this, &APSG_LightToggle::SwitchLight);
	}
}