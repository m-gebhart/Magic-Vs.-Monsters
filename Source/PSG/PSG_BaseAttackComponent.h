// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

/// Description:
/// Base class for attack components (ranged attack, shield, melee) that involves references for controlling animation and sound.

#pragma once

#include "CoreMinimal.h"
#include "PSG_CharacterAnimInstance.h"
#include "PSG_Projectile.h"
#include "Components/ActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "VectorTypes.h" 
#include "PSG_BaseAttackComponent.generated.h"

class APSG_Character;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PSG_API UPSG_BaseAttackComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APSG_Projectile> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* SoundEffect;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIsAttacking = false;

	/** @brief coordinates for anim blend asset to define which animation from blend asset to play. (Ranged Attack: 0, 100; Melee: 100, 100; Shield: 0, 0)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnimBlendValues CombatAnimBlendValues = FAnimBlendValues(100.f, 0.f);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	APSG_Character* OwningCharacter;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPSG_CharacterAnimInstance* AnimInstance;
	
public:
	UPSG_BaseAttackComponent();

	virtual void BeginPlay() override;
	
	virtual void Attack(bool bUpdateAnim = true);
	virtual void EndAttack(bool bUpdateAnim = true);

	bool IsAttacking() const {return bIsAttacking; };

protected:
	virtual void PlayAnimation();
	virtual void PlaySound();

	//UFUNCTION()
	//virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	//Attach / Replace Component
};
