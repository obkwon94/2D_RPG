#include "Character.h"
#include "DefenceState.h"

DefenceState::DefenceState()
{

}

DefenceState::~DefenceState()
{

}

void DefenceState::Init(Character* character)
{
	State::Init(character);
}

void DefenceState::Update(float deltaTime)
{
	State::Update(deltaTime);
	
	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}
}

void DefenceState::Render()
{
	State::Render();
}

void DefenceState::Release()
{
	State::Release();
}

void DefenceState::Reset()
{
	State::Reset();
}

void DefenceState::Start()
{
	State::Start();

	int attackPoint = _character->GetDamage();
	//_hp -= attackPoint;
	_character->DecreaseHP(attackPoint);
	//if (_hp <= 0)
	if (false == _character->IsLive())
	{
		_character->SetCanMove(true);

		//stop
		_character->MoveStop();
		_character->ChangeState(eStateType::ET_IDLE);
		_nextState = eStateType::ET_DEAD;
	}
	else
	{
		//_nextState = eStateType::ET_IDLE;
		_nextState = eStateType::ET_MOVE;
	}
}

void DefenceState::Stop()
{
	State::Stop();
}
