// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_ShieldBlockComponent.h"


UPSG_ShieldBlockComponent::UPSG_ShieldBlockComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSG_ShieldBlockComponent::Attack(bool bUpdateAnim)
{
	PlaySound();
	if (bUpdateAnim)
		PlayAnimation();
	bIsAttacking = true;
}