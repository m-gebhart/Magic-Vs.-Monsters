// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#include "PSG_Debug.h"

void UPSG_Debug::DebugFloatForFrame(float val, float displayTime)
{
	GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::Yellow,FString::Printf(TEXT("%f"), val));
}

void UPSG_Debug::DebugFloatOnce(float val, float displayTime)
{
	GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::Yellow,FString::Printf(TEXT("%f"), val));
}

void UPSG_Debug::DebugStringOnce(FString text, float displayTime)
{
	GEngine->AddOnScreenDebugMessage(-1, displayTime, FColor::Blue, FString::Printf(TEXT("%s"), *text));
}
