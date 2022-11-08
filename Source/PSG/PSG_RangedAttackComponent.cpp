// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_RangedAttackComponent.h"
#include "PSG_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"


UPSG_RangedAttackComponent::UPSG_RangedAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSG_RangedAttackComponent::Attack(bool bUpdateAnim)
{
	Super::Attack();
}

void UPSG_RangedAttackComponent::FireProjectile()
{
	if (Projectile != nullptr && bIsAttacking)
	{
		UWorld* World = GetWorld();
		if (World != nullptr && OwningCharacter != nullptr)
		{
			const FRotator SpawnRotation = OwningCharacter->GetFirstPersonCameraComponent()->GetComponentRotation();
			const FVector SpawnLocation = OwningCharacter->GetRightHandSphereTrigger()->GetComponentTransform().GetLocation();
	
			FActorSpawnParameters ActorSpawnParams;
			ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
			World->SpawnActor<APSG_Projectile>(Projectile, SpawnLocation, SpawnRotation, ActorSpawnParams);
		}
	}
}