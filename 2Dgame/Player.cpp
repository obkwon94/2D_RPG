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
	if (false == _isLive)
		return;

	if (false == _state->isMoving())
	{
		eDirection direction = eDirection::NONE;
		if (GameSystem::GetInstance()->IsKeyDown(VK_UP))
		{
			//MoveStart(eDirection::UP);
			direction = eDirection::UP;
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_DOWN))
		{
			//MoveStart(eDirection::DOWN);
			direction = eDirection::DOWN;
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_LEFT))
		{
			//MoveStart(eDirection::LEFT);
			direction = eDirection::LEFT;
		}

		if (GameSystem::GetInstance()->IsKeyDown(VK_RIGHT))
		{
			//MoveStart(eDirection::RIGHT);
			direction = eDirection::RIGHT;
		}

		if (eDirection::NONE != direction)
		{
			_currentDirection = direction;
			//MoveStart();
			_state->Start();
		}
	}
}