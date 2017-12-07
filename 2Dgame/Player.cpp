#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Stage.h"
#include "Map.h"
#include "IdleState.h"
#include "MoveState.h"
#include "AttackState.h"
#include "DefenceState.h"
#include "DeadState.h"
#include "Player.h"

Player::Player(std::wstring name, std::wstring scriptName, std::wstring textureFileName) : Character(name, scriptName, textureFileName)
{
	_type = eComponentType::CT_PLAYER;
	_moveTime = 0.1f;
}

Player::~Player()
{

}

void Player::UpdateAI(float deltaTime)
{
	{
		eDirection direction = eDirection::NONE;
		if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		{
			direction = eDirection::UP;
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		{
			direction = eDirection::DOWN;
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		{
			direction = eDirection::LEFT;
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		{
			direction = eDirection::RIGHT;
		}

		//space를 누르면 아이템 먹기
		if (GameSystem::GetInstance()->IsKeyDown(VK_SPACE))
		{
			//Map* map = (Map*)ComponentSystem::GetInstance()->FindComponent(L"MapData");
			Map* map = GameSystem::GetInstance()->GetStage()->GetMap();

			std::list<Component*> componentList = map->GetTileComponentList(_tileX, _tileY);
			for (std::list<Component*>::iterator it = componentList.begin(); it != componentList.end(); it++)
			{
				Component* component = (*it);
				if (eComponentType::CT_ITEM == component->GetType())
				{
					sComponentMsgParam msgParam;
					msgParam.sender = (Component*)this;
					msgParam.receiver = component;
					msgParam.message = L"Use";
					ComponentSystem::GetInstance()->SendMsg(msgParam);
				}
			}
		}

		if (eDirection::NONE != direction)
		{
			_currentDirection = direction;
			ChangeState(eStateType::ET_MOVE);
		}
	
	}
}

Component* Player::Collision(std::list<Component*>& collisionList)
{
	for (std::list<Component*>::iterator it = collisionList.begin(); it != collisionList.end(); it++)
	{
		Component* com = (*it);
		if ((com->GetType() == eComponentType::CT_MONSTER))
		{
			return (*it);
		}
	}
	return NULL;
}

void Player::InitState()
{
	ReplaceState(eStateType::ET_IDLE, new IdleState());
	ReplaceState(eStateType::ET_MOVE, new MoveState());
	ReplaceState(eStateType::ET_ATTACK, new AttackState());
	ReplaceState(eStateType::ET_DEFENCE, new DefenceState());
	ReplaceState(eStateType::ET_DEAD, new DeadState());
}