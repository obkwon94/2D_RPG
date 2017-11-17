#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "Map.h"
#include "Sprite.h"
#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "DefenceState.h"
#include "DeadState.h"
#include "Character.h"


Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Component(name)
{
	_state = NULL;
	//_state = new MoveState();
	//_spriteList.clear();
	_moveTime = 1.0f;

	_scriptFilename = scriptName;
	_textureFilename = textureFileName;

	_hp = 10;
	_attackPoint = 3;
}

Character::~Character()
{
	//delete _state;
}

void Character::Init()
{
	/*
	WCHAR textureFilename[256];
	wsprintf(textureFilename, L"%s.png", _textureFilename.c_str());

	WCHAR scriptFilename[256];
	{

		wsprintf(scriptFilename, L"%s_left.json", _scriptFilename.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_right.json", _scriptFilename.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_up.json", _scriptFilename.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	{
		wsprintf(scriptFilename, L"%s_down.json", _scriptFilename.c_str());

		Sprite* sprite = new Sprite(textureFilename, scriptFilename);
		sprite->Init();
		_spriteList.push_back(sprite);
	}
	*/
	//character test
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
	}
	InitMove();

	{
		State* state = new IdleState();
		state->Init(this);
		_stateMap[eStateType::ET_IDLE] = state;
	}
	{
		State* state = new MoveState();
		state->Init(this);
		_stateMap[eStateType::ET_MOVE] = state;
	}
	{
		State* state = new AttackState();
		state->Init(this);
		_stateMap[eStateType::ET_ATTACK] = state;
	}
	{
		State* state = new DefenceState();
		state->Init(this);
		_stateMap[eStateType::ET_DEFENCE] = state;
	}
	{
		State* state = new DeadState();
		state->Init(this);
		_stateMap[eStateType::ET_DEAD] = state;
	}
	ChangeState(eStateType::ET_IDLE);
}

void Character::DeInit()
{
	std::map<eStateType, State*>::iterator it = _stateMap.begin();
	while (it != _stateMap.end())
	{
		State* state = it->second;
		delete state;
		it++;
	}
	_stateMap.clear();
	/*
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[i]->DeInit();
		delete _spriteList[i];
	}
	_spriteList.clear();
	*/
}

void Character::Update(float deltaTime)
{
	_state->Update(deltaTime);
	//_spriteList[(int)_currentDirection]->Update(deltaTime);
	/*
	UpdateAI(deltaTime);
	//UpadateMove(deltaTime);
	_state->Update(deltaTime);
	*/
}

void Character::Render()
{
	_state->Render();
	/*
	_spriteList[(int)_currentDirection]->SetPosition(_x, _y);
	_spriteList[(int)_currentDirection]->Render();
	*/
}

void Character::Release()
{
	_state->Release();
	/*
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[(int)_currentDirection]->Release();
	}
	*/
}

void Character::Reset()
{
	_state->Reset();
	/*
	for (int i = 0; i < _spriteList.size(); i++)
	{
		_spriteList[(int)_currentDirection]->Reset();
	}
	*/
}

void Character::DecreaseHP(int decreaseHP)
{
	_hp -= decreaseHP;
	if (_hp < 0)
	{
		_isLive = false;
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
	/*
	if (false == _isLive)
		return;

	if (false == _state->isMoving())
	{
		_currentDirection = (eDirection)(rand() % 4);
		_state->Start();
	}
	*/
	_currentDirection = (eDirection)(rand() % 4);
	ChangeState(eStateType::ET_MOVE);
}

void Character::ChangeState(eStateType stateType)
{
	/*
	_state->Stop();
	delete _state;

	_state = new MoveState();
	_state->Init(this);
	_state->Start();
	*/
	/*
	if (NULL != _state)
	{
		_state->Stop();
		delete _state;
		_state = NULL;
	}
	*/
	if (NULL != _state)
	{
		_state->Stop();
	}
	/*
	switch (stateType)
	{
	case eStateType::ET_IDLE:
		_state = new IdleState();
		break;
	case eStateType::ET_MOVE:
		_state = new MoveState();
		break;
	}
	*/
	_state = _stateMap[stateType];
	//_state->Init(this);
	_state->Start();
}

void Character::InitMove()
{
	/*
	_state->Init(this);

	_currentDirection = eDirection::DOWN;
	_targetX = 0.0f;
	_targetY = 0.0f;
	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;
	*/
	_isMoving = false;
	_currentDirection = eDirection::DOWN;
}

void Character::MoveStart(int newTileX, int newTileY)
{
	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
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
	//_state->SetMoving(true);
	_isMoving = true;
}
/*
void Character::UpadateMove(float deltaTime)
{
	if (_moveTime <= _state->GetMovingDuration())
	{
		_state->Stop();

		Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
		_x = map->GetPositionX(_tileX, _tileY);
		_y = map->GetPositionY(_tileX, _tileY);

		_moveDistancePerTimeX = 0.0f;
		_moveDistancePerTimeY = 0.0f;
	}
	else
	{
		_state->UpdateMove(deltaTime);

		float moveDistanceX = _moveDistancePerTimeX * deltaTime;
		float moveDistanceY = _moveDistancePerTimeY * deltaTime;

		_x += moveDistanceX;
		_y += moveDistanceY;
	}
}
*/

void Character::MoveStop()
{
	_isMoving = false;

	Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
	_x = map->GetPositionX(_tileX, _tileY);
	_y = map->GetPositionY(_tileX, _tileY);;

	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;
}

void Character::Moving(float deltaTime)
{
	float moveDistanceX = _moveDistancePerTimeX * deltaTime;
	float moveDistanceY = _moveDistancePerTimeY * deltaTime;
	_x += moveDistanceX;
	_y += moveDistanceY;
}

Component* Character::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		sComponentMsgParam msgParam;
		msgParam.sender = this;
		msgParam.message = L"Collision";
		msgParam.receiver = (*it);
		ComponentSystem::GetInstance()->SendMsg(msgParam);
	}
	return NULL;
}

void Character::ReceiveMessage(const sComponentMsgParam& msgParam)
{
	if (false == _isLive)
		return;

	if (L"Attack" == msgParam.message)
	{
		_attackedPoint = msgParam.attackPoint;
		ChangeState(eStateType::ET_DEFENCE);
		/*
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
		*/
	}
}