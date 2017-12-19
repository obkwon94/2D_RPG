#include "GlobalType.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "TileCell.h"
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

	switch (_updateState)
	{
	case eUpdateState::PATHFINDING:
		UpdatePathfinding();
		break;
	case eUpdateState::BUILD_PATH:
		UpdateBuildPath();
	}
}

void PathfindingState::Start()
{
	State::Start();

	_targetTileCell = _character->GetTargetTileCell();

	// 모든타일셀의 길찾기 속성 초기화
	Map* map = GameSystem::GetInstance().GetStage()->GetMap();
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

	TileCell* startTileCell = map->GetTileCell(
		_character->GetTileX(), _character->GetTileY()
	);
	//_pathfindingTileQueue.push(startTileCell);
	sPathCommand newCommand;
	newCommand.heuristic = 0.0f;
	newCommand.tileCell = startTileCell;
	_pathfindingTileQueue.push(newCommand);

	_updateState = eUpdateState::PATHFINDING;
}

void PathfindingState::Stop()
{
	State::Stop();

	while (0 != _pathfindingTileQueue.size())
	{
		_pathfindingTileQueue.pop();
	}
}

void PathfindingState::UpdatePathfinding()
{
	// 길찾기 알고리즘 시작
	if (0 != _pathfindingTileQueue.size())
	{
		// 첫번 째 노드를 꺼내서 검사
		sPathCommand command = _pathfindingTileQueue.top();
		_pathfindingTileQueue.pop();

		if (false == command.tileCell->IsPathfindingMark())
		{
			command.tileCell->PathFinded();

			wchar_t msg[256];
			swprintf(msg, L"current tile %d, %d / %d, %d\n",
				command.tileCell->GetTileX(), command.tileCell->GetTileY(), _targetTileCell->GetTileX(), _targetTileCell->GetTileY());
			OutputDebugString(msg);

			// 목표 타일이면 종료
			if (command.tileCell->GetTileX() == _targetTileCell->GetTileX() &&
				command.tileCell->GetTileY() == _targetTileCell->GetTileY())
			{
				std::list<Component*> comList = command.tileCell->GetComponentList();
				/*
				for (std::list<Component*>::iterator it = comList.begin(); it != comList.end(); it++)
				{
					
					if (eComponentType::CT_MONSTER == (*it)->GetType())
					{
						Character* monster = (Character*)(*it);

						if (command.tileCell->GetTileX() < command.tileCell->GetPrevPathfindingCell()->GetTileX())
						{
							monster->SetDirection(eDirection::RIGHT);
						}
						else if (command.tileCell->GetPrevPathfindingCell()->GetTileX() < command.tileCell->GetTileX())
						{
							monster->SetDirection(eDirection::LEFT);
						}
						else  if (command.tileCell->GetTileY() < command.tileCell->GetPrevPathfindingCell()->GetTileY())
						{
							monster->SetDirection(eDirection::DOWN);
						}
						else  if (command.tileCell->GetPrevPathfindingCell()->GetTileY() < command.tileCell->GetTileY())
						{
							monster->SetDirection(eDirection::UP);
						}
					}
					
				}
				*/

				OutputDebugString(L"Find Goal\n");
				_updateState = eUpdateState::BUILD_PATH;
				_reverseTileCell = _targetTileCell;
				return;
			}

			for (int direction = 0; direction < eDirection::NONE; direction++)
			{
				TilePosition currentTilePos;
				currentTilePos.x = command.tileCell->GetTileX();
				currentTilePos.y = command.tileCell->GetTileY();
				TilePosition nextTilePos = GetNextTilePosition(currentTilePos, (eDirection)direction);

				Map* map = GameSystem::GetInstance().GetStage()->GetMap();
				TileCell* nextTileCell = map->GetTileCell(nextTilePos);

				if ((true == map->CanMoveTileMap(nextTilePos) && false == nextTileCell->IsPathfindingMark()) ||
					(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY()))
				{
					float distanceFromStart = command.tileCell->GetDistanceFromStart() + command.tileCell->GetDistanceWeight();
					float heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);

					if (NULL == nextTileCell->GetPrevPathfindingCell())
					{
						nextTileCell->SetDistanceFromStart(distanceFromStart);
						nextTileCell->SetHeuristic(heuristic);
						nextTileCell->SetPrevPathfindingCell(command.tileCell);
						//_pathfindingTileQueue.push(nextTileCell);

						sPathCommand newCommand;
						newCommand.heuristic = heuristic;
						newCommand.tileCell = nextTileCell;
						_pathfindingTileQueue.push(newCommand);


						//몬스터, 플레이어는 제외
						//	{
						//		움직이지 않는 npc 생성. 해당 타일셀에다가 위치시킨다
						//		방향은 이전 방향을 바라보고 있게
						//	}

						if (
							!(nextTileCell->GetTileX() == _targetTileCell->GetTileX() && nextTileCell->GetTileY() == _targetTileCell->GetTileY())
							&&
							!(nextTileCell->GetTileX() == _character->GetTileX() && nextTileCell->GetTileY() == _character->GetTileY())
							)
						{
							GameSystem::GetInstance().GetStage()->CreatePathfinderNPC(nextTileCell);
						}
					}
					else
					{
						if (distanceFromStart < nextTileCell->GetDistanceFromStart())
						{
							//다시 검사
							nextTileCell->SetDistanceFromStart(distanceFromStart);
							nextTileCell->SetPrevPathfindingCell(command.tileCell);
							//_pathfindingTileQueue.push(nextTileCell); <- 포인터가 들어가고, 포인터에서 비교하는 값을 조작하면 우선순위 큐가 망가진다.

							sPathCommand newCommand;
							newCommand.heuristic = CalcAStarHeuristic(distanceFromStart, nextTileCell, _targetTileCell);
							newCommand.tileCell = nextTileCell;
							_pathfindingTileQueue.push(newCommand);
						}
					}
				}
			}
		}
	}
}

void PathfindingState::UpdateBuildPath()
{
	//거꾸로돌아가면서 길을 도출한다.
	if (NULL != _reverseTileCell)
	{
		/*
		if (_reverseTileCell->GetTileX() != _targetTileCell->GetTileX() ||
			_reverseTileCell->GetTileY() != _targetTileCell->GetTileY())
		{
			GameSystem::GetInstance().GetStage()->CreatePathfindingMark(_reverseTileCell);
			_character->PushPathTileCell(_reverseTileCell);
		}
		*/
		GameSystem::GetInstance().GetStage()->CreatePathfindingMark(_reverseTileCell);
		_character->PushPathTileCell(_reverseTileCell);
		_reverseTileCell = _reverseTileCell->GetPrevPathfindingCell();
		
	}
	else
	{
		_nextState = eStateType::ET_MOVE;
	}
}

float PathfindingState::CalcSimpleHeuristic(TileCell* tileCell, TileCell* nextTileCell, TileCell* targetTileCell)
{
	float heuristic = 0.0f;

	int diffFromCurrent = 0;
	int diffFromNext = 0;

	//x : 발견적 값을 갱신
	{
		diffFromCurrent = tileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileX() - targetTileCell->GetTileX();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;

		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}

	//y : 발견적 값을 누적 갱신
	{
		diffFromCurrent = tileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromCurrent < 0)
			diffFromCurrent = -diffFromCurrent;

		diffFromNext = nextTileCell->GetTileY() - targetTileCell->GetTileY();
		if (diffFromNext < 0)
			diffFromNext = -diffFromNext;


		if (diffFromNext < diffFromCurrent)
		{
			heuristic -= 1.0f;
		}
		else if (diffFromNext > diffFromCurrent)
		{
			heuristic += 1.0f;
		}
	}

	return heuristic;
}

float PathfindingState::CalcComplectHeuristic(TileCell* nextTileCell, TileCell* targetTileCell)
{
	int distanceW = nextTileCell->GetTileX() - targetTileCell->GetTileX();
	int distanceH = nextTileCell->GetTileY() - targetTileCell->GetTileY();

	distanceW = distanceW * distanceW;
	distanceH = distanceH * distanceH;

	float distance = (float)((double)distanceW + (double)distanceH);
	return distance;
}

float PathfindingState::CalcAStarHeuristic(float distanceFromStart, TileCell* nextTileCell, TileCell* targetTileCell)
{
	return distanceFromStart + CalcComplectHeuristic(nextTileCell, targetTileCell);
}