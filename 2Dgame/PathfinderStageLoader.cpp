#include "Stage.h"
#include "Map.h"
#include "PathfinderPlayer.h"
#include "PathfinderStageLoader.h"

PathfinderStageLoader::PathfinderStageLoader(Stage* stage)
{

}

PathfinderStageLoader::~PathfinderStageLoader()
{

}

void PathfinderStageLoader::CreateComponents(std::wstring mapName)
{
	StageParts::CreateComponents(mapName);

	//1���� ���� ����

	//1���� �÷��̾� ���� (���� ��ã�� ���� �÷��̾�� ��ȯ)
	Player* player = new PathfinderPlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
	//�� �÷��̾ �ƴ� �� �߰��� Ÿ�� ������Ʈ�� ����
	int midTileX = _stage->GetMap()->GetWidth() / 2;
	int midTileY = _stage->GetMap()->GetHeight() / 2;

	std::list<Component*> comList = _stage->GetMap()->GetTileComponentList(midTileX, midTileY);
	_stage->GetMap()->InitViewer(comList.front());
}