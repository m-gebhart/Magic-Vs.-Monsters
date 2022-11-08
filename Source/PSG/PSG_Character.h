/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Properties and Functions for Player Pawn

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PSG_CharacterStateMachine.h"
#include "PSG_MeleeAttackComponent.h"
#include "PSG_RangedAttackComponent.h"
#include "PSG_ShieldBlockComponent.h"
#include "PSG_Character.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class USceneComponent;
class UCameraComponent;
class UAnimMontage;
class USoundBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUsePrimaryItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnUseSecondaryItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInteraction);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnMelee);

UCLASS(config=Game)
class APSG_Character : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleDefaultsOnly, Category=Mesh)
	USkeletalMeshComponent* FPMeshComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FPCameraComp;

	// COMBAT SYSTEM
	
	/** @brief Trigger around left hand to recognize enemy contact */
	UPROPERTY(VisibleDefaultsOnly, Category="Combat")
	USphereComponent* FPLeftHandTrigger;

	/** @brief Trigger around right hand to recognize enemy contact */
	UPROPERTY(VisibleDefaultsOnly, Category="Combat")
	USphereComponent* FPRightHandTrigger;

	/** @brief Attack component for primary action */
	UPROPERTY(EditAnywhere, Category="Combat")
	UPSG_RangedAttackComponent* FireComponent;

	/** @brief Attack component for secondary action */
	UPROPERTY(EditAnywhere, Category="Combat")
	UPSG_ShieldBlockComponent* ShieldComponent;

	/** @brief Attack component for melee action */
	UPROPERTY(EditAnywhere, Category="Combat")
	UPSG_MeleeAttackComponent* MeleeComponent;

	UPROPERTY()
	UPSG_BaseAttackComponent* CurrentAttackComponent;

	// CHARACTER MOVEMENT
	
	/** @brief Movement Speed Factor (e.g., slowed down when walking) */
	UPROPERTY()
	float MoveFactor = 1.0f;

	/** @brief Horizontal Movement Speed */
	UPROPERTY()
	float xVelocity;

	/** @brief Vertical Movement Speed */
	UPROPERTY()
	float yVelocity;

	/** @brief Whether behaviour on releasing the button for secondary action (holding shield) is kept (i.e., not cancelled by another action ("shield-break")) */
	UPROPERTY(VisibleAnywhere, Category="Combat")
	bool bCanReleaseSecondaryAction = true;

	/** @brief Used for animation and attack cooldowns */
	UPROPERTY()
	FTimerHandle CharacterTimerHandle;

	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleRadius = 55.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CapsuleHeight = 96.f;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float TurnRateGamepad;

	/** @brief Primary delegate tied to ability function(s) (e.g., from respective attack components)*/
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUsePrimaryItem OnUsePrimaryItem;

	/** @brief Secondary delegate tied to ability function(s) (e.g., from respective attack components)*/
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnUsePrimaryItem OnUseSecondaryItem;

	/** @brief Interaction delegate tied to ability function(s) (e.g., from Interaction Trigger Objects)*/
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnInteraction OnInteraction;

	/** @brief Melee delegate tied to ability function(s) (e.g., from melee attack component)*/
	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FOnMelee OnMelee;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Interaction")
	UPSG_CharacterStateMachine* CharStateMachine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Animation")
	UPSG_CharacterAnimInstance* CharacterAnimInstance;

	/** @brief Attack cooldown for primary and melee action*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	float AttackDuration = 0.85f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bIsBlocking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bIsAttacking = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Combat")
	bool bHasWeapon = false;

public:
	APSG_Character();

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMesh1P() const { return FPMeshComp; }

	UFUNCTION(BlueprintCallable)
	UCameraComponent* GetFirstPersonCameraComponent() const { return FPCameraComp; }

	UFUNCTION(BlueprintCallable)
	USphereComponent* GetRightHandSphereTrigger() const { return FPRightHandTrigger; }

	UFUNCTION(BlueprintCallable)
	USphereComponent* GetLeftHandSphereTrigger() const { return FPLeftHandTrigger; }

	UFUNCTION(BlueprintCallable)
	UPSG_BaseAttackComponent* GetCurrentAttackComponent() const { return CurrentAttackComponent; }

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
	void ChangeState(ECharacterState newState, bool bUpdateAnimation = true);
	
	// DELEGATES
	void PrimaryActionDelegate(); //Fire (primary action button press)
	void SecondaryActionDelegate(); //Block (secondary action button hold)
	void ReleaseSecondaryActionDelegate(); //Release block button
	void DisableSecondaryActionRelease(); //cancelling secondary action (not by button press)
	void InteractionDelegate(); //Environment Interaction (interaction button press) if Interaction object is nearby
	void MeleeDelegate(); //Close Combat (tertiary action button press)
	
	// MOVEMENT
	void MoveForwardBackward(float Val);
	void MoveLeftRight(float Val);
	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);

	UFUNCTION()
	void OnCapsuleBeginCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult);

	UFUNCTION()
	void OnPunchBeginCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	DECLARE_DELEGATE_OneParam(FSneakToggleDelegate, bool);
	void ToggleSneak(bool bEnable);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	virtual void Jump() override;
	
	void SetCombatDefaultDelegateFunctions();

	bool bCanAttack();

	/** @brief Default function tied to primary action delegate */
	UFUNCTION()
	void Fire();

	/** @brief Default function tied to secondary action delegate */
	UFUNCTION()
	void Shield();

	/** @brief Default function tied to melee action delegate */
	UFUNCTION()
	void Melee();

	/** @brief set time for attack cooldown */
	UFUNCTION()
	void InitClearAttackTimer();

	/** @brief if attack has passed (cooldown ran out), then change state to IDLE */
	UFUNCTION()
	void ClearAttack();

	/** @brief If character is falling, change state to FALL */
	UFUNCTION()
	void CheckFall();
};

