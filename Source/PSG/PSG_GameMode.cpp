// Copyright Epic Games, Inc. All Rights Reserved.

#include "PSG_GameMode.h"

#include "PSG_BaseEnemy.h"
#include "PSG_Character.h"
#include "PSG_Debug.h"
#include "PSG_GameState.h"
#include "UObject/ConstructorHelpers.h"

APSG_GameMode::APSG_GameMode()
	: Super()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_FPCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	GameStateClass = APSG_GameState::StaticClass();
}

void APSG_GameMode::BeginPlay()
{
	PlayerPawn = dynamic_cast<APSG_Character*>(UGameplayStatics::GetPlayerCharacter(this->GetWorld(), 0));
}

APSG_BaseEnemy* APSG_GameMode::SpawnEnemy(FVector spawnLocation)
{
	APSG_BaseEnemy* newEnemy = nullptr;
	UWorld* world = GetWorld();
	if (world != nullptr)
	{
		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
		newEnemy = GetWorld()->SpawnActor<APSG_BaseEnemy>(EnemyBP, spawnLocation, FRotator(0.f), ActorSpawnParams);
		if(newEnemy != nullptr)
			AddEnemy(newEnemy);
	}

	return newEnemy;
}

void APSG_GameMode::AddEnemy(APSG_BaseEnemy* enemy)
{
	if (enemy != nullptr)
		GetGameState<APSG_GameState>()->AddEnemyToList(enemy);
}


void APSG_GameMode::KillEnemy(APSG_BaseEnemy* enemy)
{
	if (enemy != nullptr)
		GetGameState<APSG_GameState>()->RemoveEnemyFromList(enemy);
}
