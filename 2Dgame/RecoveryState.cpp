#include "Character.h"
#include "RecoveryState.h"

RecoveryState::RecoveryState()
{

}

RecoveryState::~RecoveryState()
{

}

void RecoveryState::Init(Character* character)
{
	State::Init(character);
}

void RecoveryState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}
}

void RecoveryState::Render()
{
	State::Render();
}

void RecoveryState::Release()
{
	State::Release();
}

void RecoveryState::Reset()
{
	State::Reset();
}

void RecoveryState::Start()
{
	State::Start();
	_curState = eStateType::ET_RECOVERY;

	_character->RecoveryHP(50);
	_character->ResetRecoveryCooltime();

	_nextState = eStateType::ET_IDLE;
}

void RecoveryState::Stop()
{
	State::Stop();
}