/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example

#include "PSG_Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PSG_BaseEnemy.h"
#include "PSG_Debug.h"
#include "Kismet/GameplayStatics.h"

APSG_Projectile::APSG_Projectile() 
{
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComp->InitSphereRadius(ProjectileRadius);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &APSG_Projectile::OnHit);		// set up a notification for when this component hits something blocking

	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComponent"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = Speed;
	ProjectileMovement->MaxSpeed = Speed;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	InitialLifeSpan = LifeSpan;
}

APSG_Projectile::APSG_Projectile(AActor* spawnedFromActor) : APSG_Projectile()
{
	 OwningActor = spawnedFromActor;
}

void APSG_Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr)
	{
		if (OtherActor != nullptr && Cast<APSG_BaseEnemy>(OtherActor) != nullptr)
		{
			UGameplayStatics::ApplyDamage(OtherActor, 10.f, nullptr, this, UDamageType::StaticClass());
			Destroy();
		}
		else if (OtherComp->IsSimulatingPhysics())
		{
			OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());
			Destroy();
		}
	}
}