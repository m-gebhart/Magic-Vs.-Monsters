/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Bullets that trigger Damage or Physics system of target. Instantiated by the Actor's AttackComponent.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSG_Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class APSG_Projectile : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	float LifeSpan = 2.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	float Speed = 3000.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Projectile)
	float ProjectileRadius = 20.f;

private:
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	UPROPERTY()
	AActor* OwningActor;
	
public:
	APSG_Projectile();
	APSG_Projectile(AActor* spawnedFromActor);
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AActor* GetOwningActor() const { return OwningActor; }
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

