// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

/// Description:
/// Trigger Box that plays an interaction of switching on / off another light source when pressing the interaction button while player is located inside that box.
/// Selected light source is defined in Blueprints and in-editor (e.g., opening doors). Bound as delegate to interaction button while being inside the box.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "Components/PointLightComponent.h"
#include "GameFramework/Actor.h"
#include "PSG_LightToggle.generated.h"

UCLASS()
class PSG_API APSG_LightToggle : public AActor
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* lightActor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ULightComponent* lightComp;

	UPROPERTY(VisibleDefaultsOnly)
	UBoxComponent* overlapComponent;
	
	UFUNCTION(BlueprintCallable)
	bool IsEnabled();

	UFUNCTION(BlueprintCallable)
	void SwitchLight();

	APSG_LightToggle();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
