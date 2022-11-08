// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Trigger Box that plays an interaction when pressing the interaction button while player is located inside that box.
/// Triggered interaction function is defined in Blueprints and in-editor (e.g., opening doors). Bound as delegate to interaction button while being inside the box.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "PSG_Character.h"
#include "Components/BoxComponent.h"
#include "PSG_Interaction.generated.h"

UCLASS()
class PSG_API APSG_Interaction : public AActor
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent)
    void OnInteraction();
	
	APSG_Interaction();
	
protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* overlapComponent;
};