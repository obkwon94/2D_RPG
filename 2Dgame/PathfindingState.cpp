#include "GlobalType.h"
#include "GameSystem.h"
#include "Stage.h"
#include "TileCell.h"
#include "Map.h"
#include "Character.h"
#include "PathfindingState.h"


PathfindingState::PathfindingState()
{

}

PathfindingState::~PathfindingState()
{

}

void PathfindingState::Init(Character* character)
{
	State::Init(character);
}

void PathfindingState::Update(float deltaTime)
{
	State::Update(deltaTime);

	if (eStateType::ET_NONE != _nextState)
	{
		_character->ChangeState(_nextState);
		return;
	}

	//길찾기 알고리즘 시작
	if (0 != _pathfindingTileQueue.size())
	{
		//첫 번째 노드를 꺼내서 검사
		TileCell* tileCell = _pathfindingTileQueue.front();
		_pathfindingTileQueue.pop();

		if (false == tileCell->IsPathfindingMark())
		{
			tileCell->PathFinded();

			wchar_t msg[256];
			swprintf(msg, L"current tile %d, %d / %d, %d\n", tileCell->GetTileX(), tileCell->GetTileY(), _targetTileCell->GetTileX(), _targetTileCell->GetTileY());
			OutputDebugString(msg);

			//목표 타일이면 종료
			if (tileCell->GetTileX() == _targetTileCell->GetTileX() &&
				tileCell->GetTileY() == _targetTileCell->GetTileY())
			{
				std::list<Component*> comList = tileCell->GetComponentList();
				for (std::list<Component*>::iterator it = comList.begin(); it != comList.end(); it++)
				{
					if (eComponentType::CT_MONSTER == (*it)->GetType())
					{
						Character* monster = (Character*)(*it);

						if (tileCell->GetTileX() < tileCell->GetPrevPathfindingCell()->GetTileX())
						{
							monster->SetDirection(eDirection::RIGHT);
						}
						else if (tileCell->GetPrevPathfindingCell()->GetTileX() < tileCell->GetTileX())
						{
							monster->SetDirection(eDirection::LEFT);
						}
						else if (tileCell->GetTileY() < tileCell->GetPrevPathfindingCell()->GetTileY())
						{
							monster->SetDirection(eDirection::DOWN);
						}
						else if (tileCell->GetPrevPathfindingCell()->GetTileY() < tileCell->GetTileY())
						{
							monster->SetDirection(eDirection::UP);
						}
					}
				}
				OutputDebugString(L"Find Goal\n");
				_nextState = eStateType::ET_IDLE;
				return;
			}

			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = tileCell->GetTileX();
				currentTilePos.y = tileCell->GetTileY();
				TilePosition nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);
				
				Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);

				if (
					(true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathfindingMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()) 
				   )
				{
					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						nextTileCell->SetPrevPathfindingCell(tileCell);
						_pathfindingTileQueue.push(nextTileCell);

						if (//몬스터, 플레이어는 제외
								!(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()) &&
								!(nextTileCell->GetTileX() == _character->GetTileX() && nextTileCell->GetTileY() == _character->GetTileY())
						   )
						{
							//움직이지 않는 npc 생성, 해당 타일셀에 위치
							//방향은 이전 방향을 바라보고 있게 한다
						}
					}
				}
			}
		}
	}
}

void PathfindingState::Start()
{
	State::Start();

	_targetTileCell = _character->GetTargetTileCell();

	//모든 타일셀의 길찾기 속성 초기화
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();
	int height = map->GetHeight();
	int width = map->GetWidth();
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			TileCell* tileCell = map->GetTileCell(x, y);
			tileCell->InitPathfinding();
		}
	}

	TileCell* startTileCell = map->GetTileCell(_character->GetTileX(), _character->GetTileY());
	_pathfindingTileQueue.push(startTileCell);
}

void PathfindingState::Stop()
{
	State::Stop();

	while (0 != _pathfindingTileQueue.size())
	{
		_pathfindingTileQueue.pop();
	}
	
}