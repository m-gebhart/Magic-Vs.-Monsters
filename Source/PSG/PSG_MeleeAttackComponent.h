/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
/// 
/// Description:
/// Based on BaseAttackComponent. Melee action that attacks nearby enemies in front.
/// 
#pragma once

#include "CoreMinimal.h"
#include "PSG_BaseAttackComponent.h"
#include "Components/ActorComponent.h"
#include "PSG_MeleeAttackComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PSG_API UPSG_MeleeAttackComponent : public UPSG_BaseAttackComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MeleeDamageRadius = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<AActor*> IgnoreActors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ECollisionChannel> MeleeCollisionPreventionChannel;

public:
	UPSG_MeleeAttackComponent();

	void Attack(bool bUpdateAnim = true) override;
};
