#include "ComponentSystem.h"
#include "Map.h"
#include "Character.h"
#include "MoveState.h"

MoveState::MoveState()
{

}
MoveState::~MoveState()
{

}

void MoveState::Init(Character* character)
{
	State::Init(character);
	//_character = character;
	//_isMoving = false;
	_movingDuration = 0.0f;
}

void MoveState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	if (false == _character->IsLive())
		return;

	if (false == _character->IsMoving())
		return;

	//_character->UpadateMove(deltaTime);
	if (_character->GetMoveTime() <= _movingDuration)
	{
		_movingDuration = 0.0f;
		_character->MoveStop();
		_character->ChangeState(eStateType::ET_IDLE);
	}
	else
	{
		_movingDuration += deltaTime;
		_character->Moving(deltaTime);
	}


}
/*
void MoveState::UpdateMove(float deltaTime)
{
	_movingDuration += deltaTime;
}

bool MoveState::isMoving()
{
	return _isMoving;
}

void MoveState::SetMoving(bool isMoving)
{
	_isMoving = isMoving;
}

float MoveState::GetMovingDuration()
{
	return _movingDuration;
}
*/
void MoveState::Start()
{
	State::Start();

	if (true == _character->IsMoving())
		return;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
	
	int newTileX = _character->GetTileX();
	int newTileY = _character->GetTileY();

	switch (_character->GetDirection())
	{
	case eDirection::LEFT:			//left
		newTileX--;
		if (newTileX < 0)
			newTileX = 0;
		break;

	case eDirection::RIGHT:			//right
		newTileX++;
		if (49 < newTileX)
			newTileX = 49;
		break;

	case eDirection::UP:			//up
		newTileY--;
		if (newTileY < 0)
			newTileY = 0;
		break;

	case eDirection::DOWN:			//down
		newTileY++;
		if (49 < newTileY)
			newTileY = 49;
		break;
	}

	std::list<Component*> collisionList;
	bool canMove = map->GetTileCollisionList(newTileX, newTileY, collisionList);
	if (false == canMove)
	{
		Component* target = _character->Collision(collisionList);
		if (NULL != target && _character->IsAttackCooltime())
		{
			_character->ResetAttackCooltime();
			_character->SetTarget(target);
			_nextState = eStateType::ET_ATTACK;
		}
		else
		{
			_nextState = eStateType::ET_IDLE;
		}
		return;
	}
	else
	{
		//_isMoving = true;
		_character->MoveStart(newTileX, newTileY);
	}
}

void MoveState::Stop()
{
	State::Stop();
	/*
	_movingDuration = 0.0f;
	_isMoving = false;
	*/
}