// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#include "PSG_Character.h"

#include "PSG_BaseEnemy.h"
#include "PSG_CharacterStateMachine.h"
#include "PSG_Projectile.h"
#include "PSG_Debug.h"
#include "PSG_GameMode.h"
#include "PSG_ShieldBlockComponent.h"
#include "VectorTypes.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/InputSettings.h"


APSG_Character::APSG_Character()
{
	GetCapsuleComponent()->InitCapsuleSize(CapsuleRadius, CapsuleHeight);

	TurnRateGamepad = 45.f;

	/*Camera*/
	FPCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FPCameraComp->SetupAttachment(GetCapsuleComponent());
	FPCameraComp->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
	FPCameraComp->bUsePawnControlRotation = true;

	/*Skeleton Mesh including arms*/
	FPMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	FPMeshComp->SetupAttachment(FPCameraComp);
	FPMeshComp->SetOnlyOwnerSee(false);
	FPMeshComp->bCastDynamicShadow = false;
	FPMeshComp->CastShadow = false;
	FPMeshComp->SetRelativeRotation(FRotator(1.9f, -19.19f, 5.2f));
	FPMeshComp->SetRelativeLocation(FVector(-0.5f, -4.4f, -155.7f));
	
	/*Collision for Melee Combat*/
	const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	FPLeftHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollision"));
	FPLeftHandTrigger->SetSphereRadius(0.4f);
	FPLeftHandTrigger->AttachToComponent(FPMeshComp, AttachmentRules, "LHandSocket");

	FPRightHandTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollision"));
	FPLeftHandTrigger->SetSphereRadius(0.4f);
	FPRightHandTrigger->AttachToComponent(FPMeshComp, AttachmentRules, "RHandSocket");

	FireComponent = CreateDefaultSubobject<UPSG_RangedAttackComponent>(TEXT("RangedAttackComponent"));
	MeleeComponent = CreateDefaultSubobject<UPSG_MeleeAttackComponent>(TEXT("MeleeAttackComponent"));
	ShieldComponent = CreateDefaultSubobject<UPSG_ShieldBlockComponent>(TEXT("ShieldBlockComponent"));
}

void APSG_Character::BeginPlay()
{
	Super::BeginPlay();
	CharStateMachine = NewObject<UPSG_CharacterStateMachine>();

	CharacterAnimInstance = static_cast<UPSG_CharacterAnimInstance*>(FPMeshComp->GetAnimInstance());
	
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APSG_Character::OnCapsuleBeginCollision);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);

	SetCombatDefaultDelegateFunctions();
	
	//FPLeftHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &APSG_Character::OnPunchBeginCollision);
	FPRightHandTrigger->OnComponentBeginOverlap.AddDynamic(this, &APSG_Character::OnPunchBeginCollision);
}

void APSG_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("PrimaryAction", IE_Pressed, this, &APSG_Character::PrimaryActionDelegate);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Pressed, this, &APSG_Character::SecondaryActionDelegate);
	PlayerInputComponent->BindAction("SecondaryAction", IE_Released, this, &APSG_Character::ReleaseSecondaryActionDelegate);
	PlayerInputComponent->BindAction("Interaction", IE_Pressed, this, &APSG_Character::InteractionDelegate);
	PlayerInputComponent->BindAction("Melee", IE_Pressed, this, &APSG_Character::MeleeDelegate);
	PlayerInputComponent->BindAction<FSneakToggleDelegate>("Sneak", IE_Pressed, this, &APSG_Character::ToggleSneak, true);
	PlayerInputComponent->BindAction<FSneakToggleDelegate>("Sneak", IE_Released, this, &APSG_Character::ToggleSneak, false);

	PlayerInputComponent->BindAxis("Move Forward / Backward", this, &APSG_Character::MoveForwardBackward);
	PlayerInputComponent->BindAxis("Move Right / Left", this, &APSG_Character::MoveLeftRight);
	
	PlayerInputComponent->BindAxis("Turn Right / Left Mouse", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Look Up / Down Mouse", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn Right / Left Gamepad", this, &APSG_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("Look Up / Down Gamepad", this, &APSG_Character::LookUpAtRate);
}

void APSG_Character::SetCombatDefaultDelegateFunctions()
{
	OnUsePrimaryItem.AddDynamic(this, &APSG_Character::Fire);
	OnUseSecondaryItem.AddDynamic(this, &APSG_Character::Shield);
	OnMelee.AddDynamic(this, &APSG_Character::Melee);
}

void APSG_Character::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	OnUsePrimaryItem.RemoveDynamic(this, &APSG_Character::Fire);
	OnUseSecondaryItem.RemoveDynamic(this, &APSG_Character::Shield);
	OnMelee.RemoveDynamic(this, &APSG_Character::Melee);
}


void APSG_Character::ChangeState(ECharacterState newState, bool bUpdateAnimation)
{
	if (CharStateMachine->CurrentState != newState)
	{
		CharStateMachine->SetState(newState);
		if (bUpdateAnimation)
			CharacterAnimInstance->UpdateState();
	}
}

void APSG_Character::PrimaryActionDelegate()
{
	OnUsePrimaryItem.Broadcast();
}

void APSG_Character::SecondaryActionDelegate()
{
	OnUseSecondaryItem.Broadcast();
	bCanReleaseSecondaryAction = true;
}

void APSG_Character::ReleaseSecondaryActionDelegate()
{
	if (bCanReleaseSecondaryAction)
	{
		ChangeState(ECharacterState::IDLE);
		ShieldComponent->EndAttack(false);
	}
	bCanReleaseSecondaryAction = true;
}

void APSG_Character::DisableSecondaryActionRelease()
{
	bCanReleaseSecondaryAction = false;
}

void APSG_Character::MeleeDelegate()
{
	OnMelee.Broadcast();
}

void APSG_Character::InteractionDelegate()
{
	OnInteraction.Broadcast();
}

void APSG_Character::MoveForwardBackward(float Value)
{
	xVelocity = GetVelocity().X;
	
	if (!CharStateMachine->IsMidAir())
	{
		if (Value != 0.0f)
		{
			AddMovementInput(GetActorForwardVector(), Value * MoveFactor);
			if (!CharStateMachine->IsInCombat())
				ChangeState(MoveFactor < 1.f ? ECharacterState::WALK : ECharacterState::RUN);
		}
		else if (abs(yVelocity) < 1.f)
		{
			if (!CharStateMachine->IsInCombat())
				ChangeState(ECharacterState::IDLE);
		}

		CheckFall();
		CharacterAnimInstance->UpdateSpeed(MoveFactor);
	}
}

void APSG_Character::MoveLeftRight(float Value)
{
	yVelocity = GetVelocity().Y;
	if (Value != 0.0f)
	{
		AddMovementInput(GetActorRightVector(), Value * MoveFactor);
	}
	else if (abs(xVelocity) < 1.f && !CharStateMachine->IsMidAir())
	{
		if (!CharStateMachine->IsInCombat())
			ChangeState(ECharacterState::IDLE);
	}
	
	CheckFall();
}

void APSG_Character::ToggleSneak(bool bEnable)
{
	MoveFactor = bEnable ? 0.5f : 1.f;
}

void APSG_Character::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APSG_Character::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * TurnRateGamepad * GetWorld()->GetDeltaSeconds());
}

void APSG_Character::Jump()
{
	Super::Jump();
	if (!CharStateMachine->IsInCombat()) /*cancel jump animation if punching*/
		ChangeState(ECharacterState::JUMP);
}

bool APSG_Character::bCanAttack()
{
	return (CurrentAttackComponent == nullptr
		|| (CurrentAttackComponent != nullptr
			&& (!CurrentAttackComponent->IsAttacking() || CharStateMachine->IsCurrentState(ECharacterState::BLOCK))));
}


void APSG_Character::Fire()
{
	if (!bCanAttack()) //can only cancel Block animation
		return;

	CurrentAttackComponent = dynamic_cast<UPSG_BaseAttackComponent*>(FireComponent);
	if (CurrentAttackComponent != nullptr)
		CurrentAttackComponent->Attack();
	
	ChangeState(ECharacterState::RANGEDATTACK);
	InitClearAttackTimer();
	DisableSecondaryActionRelease();
}

void APSG_Character::Shield()
{
	if ((CurrentAttackComponent != nullptr && CurrentAttackComponent->IsAttacking()) || CharStateMachine->IsCurrentState(ECharacterState::BLOCK)) //cannot cancel another attack
		return;
	
	CurrentAttackComponent = dynamic_cast<UPSG_ShieldBlockComponent*>(ShieldComponent);
	if (CurrentAttackComponent != nullptr)
		CurrentAttackComponent->Attack();

	ChangeState(ECharacterState::BLOCK);
}

void APSG_Character::Melee()
{
	if (!bCanAttack()) //cannot cancel another attack
		return;
	
	CurrentAttackComponent = dynamic_cast<UPSG_BaseAttackComponent*>(MeleeComponent);
	if (CurrentAttackComponent != nullptr)
		CurrentAttackComponent->Attack();
	
	ChangeState(ECharacterState::MELEEATTACK);
	InitClearAttackTimer();
	DisableSecondaryActionRelease();
}

void APSG_Character::InitClearAttackTimer()
{
	GetWorld()->GetTimerManager().SetTimer(CharacterTimerHandle, this, &APSG_Character::ClearAttack, AttackDuration, false);
}

void APSG_Character::ClearAttack()
{
	ChangeState(ECharacterState::IDLE);
	if (CurrentAttackComponent != nullptr)
		CurrentAttackComponent->EndAttack();
}

void APSG_Character::CheckFall()
{
	if (GetVelocity().Z < 0 && CharStateMachine->IsMovingOnGround() && !CharStateMachine->IsInCombat())
		ChangeState(ECharacterState::FALL);	
}


void APSG_Character::OnCapsuleBeginCollision(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& SweepResult)
{
	if (CharStateMachine->IsMidAir() && HitComponent->GetComponentTransform().GetLocation().Z > SweepResult.ImpactPoint.Z)
	{
		ChangeState(ECharacterState::IDLE);
	}
}

void APSG_Character::OnPunchBeginCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (CharStateMachine->IsInCombat())
		if (dynamic_cast<APSG_BaseEnemy*>(OtherActor) != nullptr && CurrentAttackComponent == MeleeComponent && CurrentAttackComponent->IsAttacking())
			UPSG_Debug::DebugStringOnce("Meleeeee!");
}
