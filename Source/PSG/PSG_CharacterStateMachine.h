/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Provides states and template for creating a finite state machine.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PSG_CharacterStateMachine.generated.h"

UENUM(BlueprintType)
enum class ECharacterState : uint8
{
	IDLE = 0	UMETA(DisplayName = "Idle"),
	WALK = 1	UMETA(DisplayName = "Walk"),
	RUN = 2     UMETA(DisplayName = "Run"),
	JUMP = 3	UMETA(DisplayName = "Jump"),
	FALL = 4	UMETA(DisplayName = "Fall"),
	BLOCK = 5	UMETA(DisplayName = "Block"),
	RANGEDATTACK = 6	UMETA(DisplayName = "RangedAttack"),
	MELEEATTACK = 7		UMETA(DisplayName = "MeleeAttack")
};

UCLASS()
class PSG_API UPSG_CharacterStateMachine : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECharacterState CurrentState = ECharacterState::IDLE;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECharacterState PreviousState = ECharacterState::IDLE;
	
	UPSG_CharacterStateMachine() = default;
	UPSG_CharacterStateMachine(ECharacterState initState);
	
	UFUNCTION(BlueprintCallable)
	void SetState(ECharacterState newState);

	UFUNCTION(BlueprintCallable)
	bool IsCurrentState(ECharacterState state) { return CurrentState == state; }

	UFUNCTION(BlueprintCallable)
	bool IsMovingOnGround();

	UFUNCTION(BlueprintCallable)
	bool IsMidAir();

	UFUNCTION(BlueprintCallable)
	bool IsInCombat();
};