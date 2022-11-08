/// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example
///
/// Description:
/// Game Management class that keeps track of changing properties in-game. Belongs to Game Mode class that controls function calls of Game State.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "PSG_GameState.generated.h"

class APSG_BaseEnemy;

UCLASS()
class PSG_API APSG_GameState : public AGameState
{
	GENERATED_BODY()

public:
	TDoubleLinkedList<APSG_BaseEnemy*> ListEnemies;
	
	APSG_GameState();

	void AddEnemyToList(APSG_BaseEnemy* enemyToAdd);
	void RemoveEnemyFromList(APSG_BaseEnemy* enemyToRemove);
};
