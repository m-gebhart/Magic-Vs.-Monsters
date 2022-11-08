// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Based on BaseAttackComponent. Secondary action that creates invisible box preventing enemy attacks.

#pragma once

#include "CoreMinimal.h"
#include "PSG_BaseAttackComponent.h"
#include "Components/ActorComponent.h"
#include "PSG_ShieldBlockComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PSG_API UPSG_ShieldBlockComponent : public UPSG_BaseAttackComponent
{
	GENERATED_BODY()

public:
	UPSG_ShieldBlockComponent();

	void Attack(bool bUpdateAnim = true) override;
};
