/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Game Management class that defines rules (e.g., which enemy to Spawn) of the current level. Controls properties in Game State.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PSG_GameMode.generated.h"

class APSG_GameState;
class APSG_Character;
class APSG_BaseEnemy;

UCLASS()
class APSG_GameMode : public AGameMode
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly);
	APSG_Character* PlayerPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class APSG_BaseEnemy> EnemyBP;
	
	APSG_GameMode();

	APSG_BaseEnemy* SpawnEnemy(FVector spawnLocation);
	void AddEnemy(APSG_BaseEnemy* enemy);
	void KillEnemy(APSG_BaseEnemy* enemy);
	//void KillPlayer();

protected:
	virtual void BeginPlay() override;
};



