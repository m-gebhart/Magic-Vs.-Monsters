// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
//
/// Description:
/// Based on BaseAttackComponent. Primary action that spawns projectiles firing at enemies.

#pragma once

#include "CoreMinimal.h"
#include "PSG_BaseAttackComponent.h"
#include "Components/ActorComponent.h"
#include "PSG_RangedAttackComponent.generated.h"

class APSG_Character;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PSG_API UPSG_RangedAttackComponent : public UPSG_BaseAttackComponent
{
	GENERATED_BODY()

public:
	UPSG_RangedAttackComponent();

	void Attack(bool bUpdateAnim = true) override;

	/*Intended to be called by Animation*/
	UFUNCTION(BlueprintCallable)
	void FireProjectile();
};
