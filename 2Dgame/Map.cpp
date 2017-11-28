#include <fstream>

#include "GameSystem.h"
#include "TileObject.h"
#include "LifeTileObject.h"
#include "Sprite.h"
#include "Map.h"


Map::Map(std::wstring name) : Component(name)
{
	_startX = 0.0f;
	_startY = 0.0f;
	_deltaX = 0.0f;
	_deltaY = 0.0f;
	
	_spriteList.clear();
}

Map::~Map()
{

}

void Map::Init()
{
	// 맵용 스프라이트 리스트 작업
	// 32 * 32 크기의 타일
	// 16 * 16 = 256개의 타일 생성
	// 찍을 인덱스 순서대로 리스트에 푸쉬
	int srcX = 0;
	int srcY = 0;
	_width = 16;
	_height = 16;
	_tileSize = 32;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			Sprite* sprite = new Sprite(L"snowMapSprite.png", L"MapSprite.json");
			sprite->Init(srcX, srcY, 32, 32, 1.0f);
			_spriteList.push_back(sprite);

			srcX += 32;
		}
		srcX = 0;
		srcY += 32;
	}

	std::wstring wname = _name;
	std::string name = "";
	name.assign(wname.begin(), wname.end());
	
	char layer01Name[256];
	sprintf(layer01Name, "%s_1.csv", name.c_str());

	char layer02Name[256];
	sprintf(layer02Name, "%s_2.csv", name.c_str());

	// Load Map Script (1st floor)
	{
		char record[1024*4];
		int line = 0;
		std::ifstream infile(layer01Name);
		
		while (!infile.eof())
		{
			infile.getline(record, 1024);

			char* token = strtok(record, ",");
			switch (line)
			{
			case 0:
				if (NULL != token)
				{
					token = strtok(NULL, ",");
					_width = atoi(token);
					token = strtok(NULL, ",");
					_height = atoi(token);
				}
				break;

			case 1:
				break;

			default:
				//map data
				if (NULL != token)
				{
					std::vector<TileCell*> rowList;
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);
						TileCell* tileCell = new TileCell();
						WCHAR componentName[256];
						wsprintf(componentName, L"MapData_1_%d_%d", line, x);
						TileObject* tileObject = new TileObject(componentName, _spriteList[index]);
						tileObject->SetCanMove(true);
						tileCell->AddComponent(tileObject, true);
						rowList.push_back(tileCell);
						token = strtok(NULL, ",");
					}
					_tileMap.push_back(rowList);
				}
				break;
			}
			line++;
		}
	}

	// Load Map Script (2nd floor)
	{
		char record[1024*4];
		int row = 0;
		int line = 0;
		std::ifstream infile(layer02Name);

		while (!infile.eof())
		{
			infile.getline(record, 1024);

			char* token = strtok(record, ",");
			switch (line)
			{
			case 0:
				
				break;

			case 1:
				break;

			default:
				//map data
				if (NULL != token)
				{
					std::vector<TileCell*> rowList = _tileMap[row];
					for (int x = 0; x < _width; x++)
					{
						int index = atoi(token);
						TileCell* tileCell = rowList[x];
						WCHAR componentName[256];
						wsprintf(componentName, L"MapData_02_%d_%d", line, x);
						if (0 <= index)
						{
							if (100100 == index)
							{
								LifeTileObject* lifeTileObject = new LifeTileObject(x, row, componentName, _spriteList[50]);
								lifeTileObject->SetCanMove(true);
								tileCell->AddComponent(lifeTileObject, true);
							}
							else
							{
								TileObject* tileObject = new TileObject(componentName, _spriteList[index]);
								tileCell->AddComponent(tileObject, true);
							}
						}
								
						token = strtok(NULL, ",");
					}
					row++;
				}
				break;
			}
			line++;
		}
	}
}

void Map::DeInit()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->DeInit();
			delete _tileMap[y][x];
		}
	}
}

void Map::Update(float deltaTime)
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->MoveDeltaPosition(_deltaX, _deltaY);
			_tileMap[y][x]->Update(deltaTime);
		}
	}

	if (NULL != _viewer)
	{
		float deltaX = _viewer->GetMoveDeltaX() * deltaTime;
		float deltaY = _viewer->GetMoveDeltaY() * deltaTime;
		Scroll(-deltaX, -deltaY);
	}
}

void Map::Render()
{
	int midX = GameSystem::GetInstance()->GetClientWidth() / 2;
	int midY = GameSystem::GetInstance()->GetClientHeight() / 2;

	int minX = _viewer->GetTileX() - (midX / _tileSize) - 3;
	int maxX = _viewer->GetTileX() + (midX / _tileSize) + 3;

	int minY = _viewer->GetTileY() - (midY / _tileSize) - 3;
	int maxY = _viewer->GetTileY() + (midY / _tileSize) + 3;

	if (minX < 0)
		minX = 0;

	if (_width <= maxX)
		maxX = _width ;

	if (minY < 0)
		minY = 0;

	if (_height <= maxY)
		maxY = _height ;

	for (int y = minY; y < maxY; y++)
	{
		for (int x = minX; x < maxX; x++)
		{
			_tileMap[y][x]->Render();
		}
	}
}

void Map::Release()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Release();
		}
	}
}

void Map::Reset()
{
	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->Reset();
		}
	}
}

void Map::Scroll(float deltaX, float deltaY)
{
	_deltaX = deltaX;
	_deltaY = deltaY;
}

int Map::GetPositionX(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionX();
}

int Map::GetPositionY(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetPositionY();
}

int Map::GetWidth()
{
	return _width;
}

int Map::GetHeight()
{
	return _height;
}

void Map::SetTileComponent(int tileX, int tileY, Component* component, bool isRender)
{
	_tileMap[tileY][tileX]->AddComponent(component, isRender);
}

void Map::ResetTileComponent(int tileX, int tileY, Component* component)
{
	_tileMap[tileY][tileX]->RemoveComponent(component);
}

std::list<Component*> Map::GetTileComponentList(int tileX, int tileY)
{
	return _tileMap[tileY][tileX]->GetComponentList();
}

bool Map::CanMoveTileMap(int tileX, int tileY)
{
	if (tileX < 0)
		return false;

	if (_width <= tileX)
		return false;

	if (tileY < 0)
		return false;
	return _tileMap[tileY][tileX]->CanMove();
}

bool Map::GetTileCollisionList(int tileX, int tileY, std::list<Component*>& collisionList)
{
	if (tileX < 0)
		return false;

	if (_width < 0)
		return false;

	if (tileY < 0)
		return false;

	if (_height < 0)
		return false;

	return _tileMap[tileY][tileX]->GetTileCollisionList(collisionList);
}

void Map::InitViewer(Component* viewer)
{
	_viewer = viewer;

	//뷰어를 중심으로 렌더링 할 영역을 구한다.
	int midX = GameSystem::GetInstance()->GetClientWidth() / 2;
	int midY = GameSystem::GetInstance()->GetClientHeight() / 2;

	//뷰어의 위치를 기준으로 시작 픽셀 위치를 계산
	_startX = (-_viewer->GetTileX() * _tileSize) + midX - _tileSize / 2;
	_startY = (-_viewer->GetTileY() * _tileSize) + midY - _tileSize / 2;

	//해당 위치에 타일을 그린다
	float posX = _startX;
	float posY = _startY;

	for (int y = 0; y < _height; y++)
	{
		for (int x = 0; x < _width; x++)
		{
			_tileMap[y][x]->SetPosition(posX, posY);
			posX += _tileSize;
		}
		posX = _startX;
		posY += _tileSize;
	}
}

