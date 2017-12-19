#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "IdleState.h"
#include "PathfindingState.h"
#include "PathfindingMoveState.h"
#include "PathfinderPlayer.h"


PathfinderPlayer::PathfinderPlayer(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textrueFilename) :
	Player(name, scriptName, textrueFilename)
{
}

PathfinderPlayer::~PathfinderPlayer()
{
}

void PathfinderPlayer::UpdateAI(float deltaTime)
{
	//���콺 ��ǲ ó��
	if (GameSystem::GetInstance().IsMouseDown())
	{
		int mouseX = GameSystem::GetInstance().GetMouseX();
		int mouseY = GameSystem::GetInstance().GetMouseY();

		TileCell* targetTileCell = GameSystem::GetInstance().GetStage()->GetMap()->FindTileCellWithMousePosition(mouseX, mouseY);

		//ã�� Ÿ�� ���� ���� �ƴϸ�, ��ǥ�� ������ �� ���� ã�´�.
		if (NULL != targetTileCell)
		{
			SetTargetTileCell(targetTileCell);
		}
	}
}

void PathfinderPlayer::InitState()
{
	Player::InitState();
	ReplaceState(eStateType::ET_MOVE, new PathfindingMoveState());
	//ReplaceState(eStateType::ET_ATTACK, new IdleState());
	ReplaceState(eStateType::ET_PATHFINDING, new PathfindingState());
}
