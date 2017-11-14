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
	_character = character;
	_isMoving = false;
	_movingDuration = 0.0f;
}

void MoveState::Update(float deltaTime)
{
	if (false == _character->IsLive())
		return;

	if (false == _isMoving)
		return;

	_character->UpadateMove(deltaTime);
}

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

void MoveState::Start()
{
	if (true == _isMoving)
		return;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
	
	int newTileX = _character->GetTileX();
	int newTileY = _character->GetTileY();

	//switch (direction)
	switch (_character->GetDirection())
	{
	case eDirection::LEFT:			//left
		newTileX--;
		break;

	case eDirection::RIGHT:			//right
		newTileX++;
		break;

	case eDirection::UP:			//up
		newTileY--;
		break;

	case eDirection::DOWN:			//down
		newTileY++;
		break;
	}

	std::list<Component*> collisionList;
	bool canMove = map->GetTileCollisionList(newTileX, newTileY, collisionList);
	if (false == canMove)
	{
		_character->Collision(collisionList);
		return;
	}
	else
	{
		_isMoving = true;
		_character->MoveStart(newTileX, newTileY);
	}
}

void MoveState::Stop()
{
	_movingDuration = 0.0f;
	_isMoving = false;
}