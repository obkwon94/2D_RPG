#include "LifePlayer.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "DefenceState.h"
#include "DeadState.h"

LifePlayer::LifePlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textrueFilename) : Player(name, scriptName, textrueFilename)
{
	_type = eComponentType::CT_PLAYER;
}

LifePlayer::~LifePlayer()
{

}

void LifePlayer::InitState()
{
	Player::InitState();

	ReplaceState(eStateType::ET_ATTACK, new IdleState());//Idle이 여기서 NULL역할을해줌
}