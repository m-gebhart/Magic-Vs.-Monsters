/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Passes current state of character state machine to the animator instance to align animations. Controlled by owning character of state machine (character class) and animation instance.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PSG_CharacterAnimInstance.generated.h"

USTRUCT(BlueprintType)
struct FAnimBlendValues
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float X;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Y;

	FAnimBlendValues() : X(0), Y(0) {}
	FAnimBlendValues(float x, float y) : X(x), Y(y) {};
};

UCLASS()
class PSG_API UPSG_CharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateState();	

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateSpeed(float speed);

	UFUNCTION(BlueprintImplementableEvent)
	void SetAnimBlendValues(float xBlendValue, float yBlendValue);

	UFUNCTION(BlueprintImplementableEvent)
	void ResetAnimValues();
};
