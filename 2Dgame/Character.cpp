#include "ComponentSystem.h"
#include "ComponentMessage.h"
#include "Map.h"
#include "Sprite.h"
#include "Font.h"
#include "MoveState.h"
#include "IdleState.h"
#include "AttackState.h"
#include "DefenceState.h"
#include "DeadState.h"
#include "Character.h"


Character::Character(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Component(name)
{
	_state = NULL;
	_moveTime = 1.0f;

	_scriptFilename = scriptName;
	_textureFilename = textureFileName;

	_hp = 100;
	_attackPoint = 10;
	_damage = 0;

	_attackSpeed = 0.5f;
	_attackCooltimeDuration = 0.0f;
}

Character::~Character()
{
	delete _font;
}

void Character::Init()
{
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


	//Font
	{
		D3DCOLOR color = D3DCOLOR_ARGB(255, 0, 0, 0);
		_font = new Font(L"Arial", 25, color);
		
		_font->SetRect(100, 100, 400, 100);
		UpdateText();
	}
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
}

void Character::Update(float deltaTime)
{
	UpdateAttackCooltime(deltaTime);
	_state->Update(deltaTime);
	UpdateText();
}

void Character::Render()
{
	_state->Render();

	_font->SetPosition(_x-200, _y-70);
	_font->Render();
}

void Character::Release()
{
	_state->Release();
}

void Character::Reset()
{
	_state->Reset();
}

void Character::IncreaseHP(int increaseHP)
{
	_hp += increaseHP;
	
	if (100 <= _hp)
	{
		_hp = 100;
	}
}

void Character::DecreaseHP(int decreaseHP)
{
	_hp -= decreaseHP;
	
	if (_hp <= 0)
	{
		_isLive = false;
		_state->NextState(eStateType::ET_DEAD);
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
	_currentDirection = (eDirection)(rand() % 4);
	_state->NextState(eStateType::ET_MOVE);
}

void Character::ChangeState(eStateType stateType)
{
	if (NULL != _state)
	{
		_state->Stop();
	}
	
	_state = _stateMap[stateType];
	_state->Start();
}

void Character::InitMove()
{
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
	_isMoving = true;
}

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
	return NULL;
}

void Character::ReceiveMessage(const sComponentMsgParam& msgParam)
{
	if (false == _isLive)
		return;

	if (L"Attack" == msgParam.message)
	{
		_damage = msgParam.attackPoint;
		if (2 < rand() % 4)
		{
			_damage = _damage * 2;
		}
		_state->NextState(eStateType::ET_DEFENCE);
	}
}

void Character::UpdateAttackCooltime(float deltaTime)
{
	if (_attackCooltimeDuration < _attackSpeed)
	{
		_attackCooltimeDuration += deltaTime;
	}
	else
	{
		_attackCooltimeDuration = _attackSpeed;
	}
}

void Character::ResetAttackCooltime()
{
	_attackCooltimeDuration = 0.0f;
}

bool Character::IsAttackCooltime()
{
	if (_attackSpeed <= _attackCooltimeDuration)
	{
		return true;
	}
	return false;
}

void Character::UpdateText()
{
	if (true == _isLive)
	{
		int coolTime = (int)(_attackCooltimeDuration * 1000.0f);

		WCHAR text[256];
		wsprintf(text, L"DAMAGE %d\nHP %d\nATTACK %d", _damage, _hp, coolTime);
		_font->SetText(text);
	}
	else
	{
		WCHAR text[256];
		wsprintf(text, L"DIED");
		_font->SetText(text);
	}
}