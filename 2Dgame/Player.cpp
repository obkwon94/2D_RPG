#include "ComponentSystem.h"
#include "GameSystem.h"
#include "Map.h"
#include "MoveState.h"
#include "Player.h"

Player::Player(LPCWSTR name, LPCWSTR scriptName, LPCWSTR textureFileName) : Character(name, scriptName, textureFileName)
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