#include "ComponentSystem.h"
#include "Map.h"
#include "Sprite.h"
#include "TileObject.h"
#include "RecoveryItem.h"

RecoveryItem::RecoveryItem(LPCWSTR name, LPCWSTR scriptFilename, LPCWSTR textureFilename) : Component(name)
{
	_sprite = NULL;
	_ComponentType = eComponentType::CT_ITEM;
	_scriptFilename = scriptFilename;
	_textureFilename = textureFilename;
}

RecoveryItem::~RecoveryItem()
{

}

void RecoveryItem::Init()
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");

	int tileX = rand() % (map->GetWidth() - 1) + 1;
	int tileY = rand() % (map->GetHeight() - 1) + 1;
	while (1)
	{
		if (true == map->CanMoveTileMap(tileX, tileY))
		{
			_tileX = tileX;
			_tileY = tileY;
			break;
		}
		tileX = rand() % (map->GetWidth() - 1) + 1;
		tileY = rand() % (map->GetHeight() - 1) + 1;
	}
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);
	map->SetTileComponent(_tileX, _tileY, this, true);
	
	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _textureFilename.c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s.json", _scriptFilename.c_str());
		_sprite = new Sprite(textureFilename, scriptFilename);
		_sprite->Init();
	}

	_canMove = true;
}

void RecoveryItem::DeInit()
{
	_sprite->DeInit();
}

void RecoveryItem::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void RecoveryItem::Render()
{
	_sprite->SetPosition(_x, _y);
	_sprite->Render();
}

void RecoveryItem::Release()
{
	_sprite->Release();
}

void RecoveryItem::Reset()
{
	_sprite->Reset();
}

void RecoveryItem::SetPosition(float posX, float posY)
{
	_x = posX;
	_y = posY;
}

void RecoveryItem::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}