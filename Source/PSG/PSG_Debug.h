// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "PSG_Debug.generated.h"

UCLASS()
class PSG_API UPSG_Debug : public UObject
{
	GENERATED_BODY()
public:
	static void DebugFloatForFrame(float val, float displayTime = 0.014f);
	static void DebugFloatOnce(float val, float displayTime = 3.f);

	static void DebugStringOnce(FString text, float displayTime = 3.f);
};
