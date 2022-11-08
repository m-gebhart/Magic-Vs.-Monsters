// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_BaseAttackComponent.h"
#include "PSG_Character.h"
#include "PSG_Debug.h"
#include "Camera/CameraComponent.h"
#include "Evaluation/Blending/MovieSceneMultiChannelBlending.h"


UPSG_BaseAttackComponent::UPSG_BaseAttackComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPSG_BaseAttackComponent::BeginPlay()
{
	Super::BeginPlay();
	OwningCharacter = dynamic_cast<APSG_Character*>(GetOwner());
	
	if (OwningCharacter != nullptr)
		AnimInstance = static_cast<UPSG_CharacterAnimInstance*>(OwningCharacter->GetMesh1P()->GetAnimInstance());
}

void UPSG_BaseAttackComponent::Attack(bool bUpdateAnim)
{
	/*if(Projectile == nullptr)
		return;*/

	bIsAttacking = true;

	PlaySound();
	if (bUpdateAnim)
		PlayAnimation();
}

void UPSG_BaseAttackComponent::EndAttack(bool bUpdateAnim)
{
	bIsAttacking = false;
	if (AnimInstance != nullptr && bUpdateAnim)
		AnimInstance->ResetAnimValues();
}

void UPSG_BaseAttackComponent::PlayAnimation()
{
	if (AnimInstance != nullptr)
	{
		AnimInstance->SetAnimBlendValues(CombatAnimBlendValues.X, CombatAnimBlendValues.Y);
	}
}

void UPSG_BaseAttackComponent::PlaySound()
{
	if (SoundEffect != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, SoundEffect, GetOwner()->GetActorLocation());
}