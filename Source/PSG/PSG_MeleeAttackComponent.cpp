// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_MeleeAttackComponent.h"
#include "PSG_Character.h"
#include "PSG_Debug.h"


UPSG_MeleeAttackComponent::UPSG_MeleeAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UPSG_MeleeAttackComponent::Attack(bool bUpdateAnim)
{
	Super::Attack();
}