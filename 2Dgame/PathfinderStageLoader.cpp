#include "Stage.h"
#include "Map.h"
#include "PathfinderPlayer.h"
#include "PathfinderMonster.h"
#include "PathfinderStageLoader.h"

PathfinderStageLoader::PathfinderStageLoader(Stage* stage) :
	StageLoader(stage)
{

}

PathfinderStageLoader::~PathfinderStageLoader()
{

}

void PathfinderStageLoader::CreateComponents(std::wstring mapName)
{
	StageLoader::CreateComponents(mapName);

	//1���� ���� ����
	Component* monster = new PathfinderMonster(L"pathfinderMonster", L"monster", L"monster");
	_stage->AddStageComponent(monster);

	//1���� �÷��̾� ���� (���� ��ã�� ���� �÷��̾�� ��ȯ)
	Player* player = new PathfinderPlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);

	TileCell* targetCell = _stage->GetMap()->GetTileCell(monster->GetTileX(), monster->GetTileY());
	player->SetTargetTileCell(targetCell);
	//�� �÷��̾ �ƴ� �� �߰��� Ÿ�� ������Ʈ�� ����
	int midTileX = _stage->GetMap()->GetWidth() / 2;
	int midTileY = _stage->GetMap()->GetHeight() / 2;

	std::list<Component*> comList = _stage->GetMap()->GetTileComponentList(midTileX, midTileY);
	_stage->GetMap()->InitViewer(comList.front());
}