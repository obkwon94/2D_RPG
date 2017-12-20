#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Stage.h"
#include "TileCell.h"
#include "Map.h"
#include "Character.h"
#include "PathfindingMoveState.h"

PathfindingMoveState::PathfindingMoveState()
{

}

PathfindingMoveState::~PathfindingMoveState()
{

}

void PathfindingMoveState::Init(Character* character)
{
	State::Init(character);
	_movingDuration = 0.0f;
}

void PathfindingMoveState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	if (false == _character->IsLive())
		return;

	if (_character->GetMoveTime() <= _movingDuration)
	{
		_movingDuration = 0.0f;
		if (0 != _pathTileCellStack.size())
		{
			TileCell* tileCell = _pathTileCellStack.top();
			_pathTileCellStack.pop();

			TilePosition to;
			to.x = tileCell->GetTileX();
			to.y = tileCell->GetTileY();

			TilePosition from;
			from.x = _character->GetTileX();
			from.y = _character->GetTileY();

			eDirection direction = GetDirection(to, from);

			if(eDirection::NONE != direction)
				_character->SetDirection(direction);

			//_character->MoveStart(tileCell->GetTileX(), tileCell->GetTileY());
			//_character->MoveStop();
			std::list<Component*> collisionList;
			bool canMove = GameSystem::GetInstance().GetStage()->GetMap()->GetTileCollisionList(to.x, to.y, collisionList);
			if (false == canMove)
			{
				Component* target = _character->Collision(collisionList);
				if (NULL != target && _character->IsAttackCooltime())
				{
					_character->ResetAttackCooltime();
					_character->SetTarget(target);
					_nextState = eStateType::ET_MEET;
				}
				else
				{
					_nextState = eStateType::ET_IDLE;
				}
			}
			else
			{
				_character->MoveStart(tileCell->GetTileX(), tileCell->GetTileY());
				_character->MoveStop();
			}
		}
		else
		{
			_nextState = eStateType::ET_IDLE;
		}
	}
	else
	{
		_movingDuration += deltaTime;
	}
}

void PathfindingMoveState::Start()
{
	State::Start();

	_nextState = eStateType::ET_NONE;

	_movingDuration = 0.0f;

	_pathTileCellStack = _character->GetPathTileCellStack();
	_pathTileCellStack.pop();
}

void PathfindingMoveState::Stop()
{
	State::Stop();
	_character->ClearPathTileCellStack();
}
