#include "GameSystem.h"
#include "ComponentSystem.h"
#include "Stage.h"
#include "Map.h"
#include "Character.h"
#include "Sprite.h"
#include "TileObject.h"
#include "RecoveryItem.h"

RecoveryItem::RecoveryItem(std::wstring name, std::wstring scriptFilename, std::wstring textureFilename) : Component(name)
{
	_sprite = NULL;
	_type = eComponentType::CT_ITEM;
	_scriptFilename = scriptFilename;
	_textureFilename = textureFilename;
	_canMove = true;
}

RecoveryItem::~RecoveryItem()
{

}

void RecoveryItem::Init()
{
	//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
	Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

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
	map->SetTileComponent(_tileX, _tileY, this, false);
	
	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _textureFilename.c_str());

	WCHAR scriptFilename[256];
	{
		wsprintf(scriptFilename, L"%s.json", _scriptFilename.c_str());
		_sprite = new Sprite(textureFilename, scriptFilename);
		_sprite->Init();
	}
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
	if (false == _isLive)
		return;

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

void RecoveryItem::ReceiveMessage(const sComponentMsgParam& msgParam)
{
	if (L"Use" == msgParam.message)
	{
		Component* sender = msgParam.sender;
		switch (sender->GetType())
		{
		case eComponentType::CT_PLAYER:
			((Character*)sender)->IncreaseHP(100);
			_isLive = false;
			break;

		case eComponentType::CT_NPC:
			break;

		case eComponentType::CT_MONSTER:
			break;

		}
	}
	
}
