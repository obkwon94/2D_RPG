#include "ComponentSystem.h"
#include "Character.h"

#include "DefenseState.h"


DefenseState::DefenseState()
{
}

DefenseState::~DefenseState()
{
}

void DefenseState::Init(Character* character)
{
	State::Init(character);
}

void DefenseState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}
}

void DefenseState::Render()
{
	State::Render();
}

void DefenseState::Reset()
{
	State::Reset();
}

void DefenseState::Release()
{
	State::Release();
}

void DefenseState::Start()
{
	State::Start();

	int attackPoint = _character->GetAttackedPoint();
	_character->DecreaseHP(attackPoint);
	
	if (false == _character->IsLive())
	{
		_character->SetCanMove(true);
		_character->MoveStop();
		_nextState = eStateType::ET_DEAD;
	}
	else
	{
		_nextState = eStateType::ET_MOVE;
	}
}

void DefenseState::Stop()
{
	State::Stop();
}

