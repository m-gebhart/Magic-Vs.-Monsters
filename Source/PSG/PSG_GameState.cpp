// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_GameState.h"

#include "PSG_BaseEnemy.h"
#include "PSG_Debug.h"

APSG_GameState::APSG_GameState() : Super()
{
}

void APSG_GameState::AddEnemyToList(APSG_BaseEnemy* enemyToAdd)
{
	ListEnemies.AddTail(enemyToAdd);
}

void APSG_GameState::RemoveEnemyFromList(APSG_BaseEnemy* enemyToRemove)
{
	ListEnemies.RemoveNode(ListEnemies.FindNode(enemyToRemove));
	if (ListEnemies.IsEmpty())
		UPSG_Debug::DebugStringOnce("Is Empty!");
}