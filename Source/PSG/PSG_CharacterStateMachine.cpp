// Magic vs. Monsters - by Michael Gebhart. Project's foundation is based on Epic's FirstPersonShooter Example


#include "PSG_CharacterStateMachine.h"

UPSG_CharacterStateMachine::UPSG_CharacterStateMachine(ECharacterState initState)
{
	CurrentState = initState;
}

void UPSG_CharacterStateMachine::SetState(ECharacterState newState)
{
	if (CurrentState != newState)
	{
		PreviousState = CurrentState;
		CurrentState = newState;
	}
}

bool UPSG_CharacterStateMachine::IsMovingOnGround()
{
	return CurrentState == ECharacterState::WALK ||
		CurrentState == ECharacterState::RUN;
}

bool UPSG_CharacterStateMachine::IsMidAir()
{
	return CurrentState == ECharacterState::FALL ||
		CurrentState == ECharacterState::JUMP;
}

bool UPSG_CharacterStateMachine::IsInCombat()
{
	return CurrentState == ECharacterState::RANGEDATTACK ||
			CurrentState == ECharacterState::MELEEATTACK ||
			CurrentState == ECharacterState::BLOCK;
}
