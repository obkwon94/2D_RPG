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

	//1개의 몬스터 생성

	//1개의 플레이어 생성 (추후 길찾기 전용 플레이어로 전환)
	Player* player = new PathfinderPlayer(L"player", L"player", L"player");
	_stage->AddStageComponent(player);
	//뷰어를 플레이어가 아닌 맵 중간에 타일 오브젝트로 세팅
	int midTileX = _stage->GetMap()->GetWidth() / 2;
	int midTileY = _stage->GetMap()->GetHeight() / 2;

	std::list<Component*> comList = _stage->GetMap()->GetTileComponentList(midTileX, midTileY);
	_stage->GetMap()->InitViewer(comList.front());
}