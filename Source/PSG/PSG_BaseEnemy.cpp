// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_BaseEnemy.h"

#include "PSG_Debug.h"
#include "PSG_GameMode.h"
#include "PSG_GameState.h"
#include "Kismet/GameplayStatics.h"


APSG_BaseEnemy::APSG_BaseEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APSG_BaseEnemy::BeginPlay()
{
	((APSG_GameState*)UGameplayStatics::GetGameState(GetWorld()))->AddEnemyToList(this);
}


float APSG_BaseEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UPSG_Debug::DebugStringOnce("GOT DAMAGE");
	((APSG_GameMode*)UGameplayStatics::GetGameMode(GetWorld()))->KillEnemy(this);
	return 0;
}