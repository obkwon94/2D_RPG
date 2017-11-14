#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "Sprite.h"
#include "Character.h"
#include "Map.h"

Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Component(name)
{

	_spriteList.clear();
	_moveTime = 1.0f;
	_scriptName = scriptName;
	_textureFileName = textureFileName;

	_hp = 10;
	_attackPoint = 3;
}

Character::~Character()
{

}

void Character::Init()
{
	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _textureFileName.c_str());

	WCHAR scriptFilename[256];
	{
	
		wsprintf(scriptFilename, L"%s_left.json", _scriptName.c_str());
		
		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_right.json", _scriptName.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_up.json", _scriptName.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_down.json", _scriptName.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	
	//character test
	{
		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
		

		_tileX = rand()% (map->GetWidth() - 1) +1 ;
		_tileY = rand() % (map->GetHeight() - 1) + 1;
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);
		map->SetTileComponent(_tileX, _tileY, this, true);
	}
	InitMove();
}

void Character::DeInit()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DeInit();
		delete _spriteList[i];
	}
	_spriteList.clear();
}

void Character::Update(float deltaTime)
{
	_spriteList[(int)_currentDirection]->Update(deltaTime);

	UpdateAI(deltaTime);
	UpadateMove(deltaTime);
}

void Character::Render()
{
	_spriteList[(int)_currentDirection]->SetPosition(_x, _y);
	_spriteList[(int)_currentDirection]->Render();
}

void Character::Release()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[(int)_currentDirection]->Release();
	}
}

void Character::Reset()
{
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[(int)_currentDirection]->Reset();
	}
}

void Character::SetPosition(float posX, float posY)
{
	_x = posX;
	_y = posY;
}

void Character::MoveDeltaPosition(float deltaX, float deltaY)
{
	_x += deltaX;
	_y += deltaY;
}

void Character::UpdateAI(float deltaTime)
{
	if (false == _isLive)
		return;

	if (false == _isMoving)
	{
		int direction = rand() % 4;
		MoveStart((eDirection)direction);
	}
}

void Character::InitMove()
{
	_isMoving = false;
	
	_movingDuration = 0.0f;
	_currentDirection = eDirection::DOWN;
	_targetX = 0.0f;
	_targetY = 0.0f;
	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;

}

void Character::MoveStart(eDirection direction)
{
	if (true == _isMoving)
		return;

	_currentDirection = direction;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
	map->ResetTileComponent(_tileX, _tileY, this);
	
	int newTileX = _tileX;
	int newTileY = _tileY;
	
	switch (direction)
	{
	case eDirection::LEFT:			//left
		newTileX--;
		if (newTileX < 0)
			newTileX = 0;
		break;
	case eDirection::RIGHT:			//right
		newTileX++;
		if (49 < newTileX)
			newTileX = 49;
		break;
	case eDirection::UP:			//up
		newTileY--;
		if (newTileY < 0)
			newTileY = 0;
		break;
	case eDirection::DOWN:			//down
		newTileY++;
		if (49 < newTileY)
			newTileY = 49;
		break;
	}
	
	std::list<Component*> collisionList;
	bool canMove = map->GetTileCollisionList(newTileX, newTileY, collisionList);
	if (false == canMove)
	{
		Collision(collisionList);
		return;
	}
	
	map->ResetTileComponent(_tileX, _tileY, this);

	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);

	_tileX = newTileX;
	_tileY = newTileY;

	map->SetTileComponent(_tileX, _tileY, this, true);

	//자연스러운 움직임을 위한 보간 작업
	{
		map->SetTileComponent(_tileX, _tileY, this, false);
		
		//이동거리
		_targetX = map->GetPositionX(_tileX, _tileY);
		_targetY = map->GetPositionY(_tileX, _tileY);

		float distanceX = _targetX - _x;
		float distanceY = _targetY - _y;

		//최소 이동거리
		_moveDistancePerTimeX = distanceX / _moveTime;
		_moveDistancePerTimeY = distanceY / _moveTime;
	}
	_isMoving = true;
}

void Character::UpadateMove(float deltaTime)
{
	if (false == _isLive)
		return;

	if (false == _isMoving)
		return;

	if (_moveTime <= _movingDuration)
	{
		_movingDuration = 0.0f;
		_isMoving = false;

		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		_moveDistancePerTimeX = 0.0f;
		_moveDistancePerTimeY = 0.0f;
	}
	else
	{
		_movingDuration += deltaTime;

		float moveDistanceX = _moveDistancePerTimeX * deltaTime;
		float moveDistanceY = _moveDistancePerTimeY * deltaTime;

		_x += moveDistanceX;
		_y += moveDistanceY;
	}
}

void Character::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		sComponentMsgParam msgParam;
		msgParam.sender = this;
		msgParam.message = L"Collision";
		msgParam.receiver = (*it);
		//ComponentSystem::GetInstance()->SendMsg(L"Collision", (*it), msgParam);
		ComponentSystem::GetInstance()->SendMsg(msgParam);
	}
}
//void Character::ReceiveMessage(std::wstring message, const sComponentMsgParam& msgParam)
void Character::ReceiveMessage(const sComponentMsgParam& msgParam)
{
	if (false == _isLive)
		return;

	if (L"Attack" == msgParam.message)
	{
		int attackPoint = msgParam.attackPoint;
		_hp -= attackPoint;
		if (_hp <= 0)
		{
			_isLive = false;
			SetCanMove(true);

			//stop
			_moveDistancePerTimeX = 0.0f;
			_moveDistancePerTimeY = 0.0f;
		}
	}
}