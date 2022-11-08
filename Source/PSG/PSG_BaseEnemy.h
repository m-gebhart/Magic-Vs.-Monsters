/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example/// Description:
/// 
/// Description:
/// Triggering damage system if attacked by player.



#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PSG_BaseEnemy.generated.h"

UCLASS()
class PSG_API APSG_BaseEnemy : public AActor
{
	GENERATED_BODY()

public:
	APSG_BaseEnemy();

protected:
	virtual void BeginPlay() override;;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
