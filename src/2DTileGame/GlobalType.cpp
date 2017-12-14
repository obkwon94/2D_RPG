#include "GlobalType.h"

TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction)
{
	TilePosition tilePosition = currentTilePos;
	switch (direction)
	{
	case eDirection::LEFT:	// left
		tilePosition.x--;
		break;
	case eDirection::RIGHT:	// right
		tilePosition.x++;
		break;
	case eDirection::UP:	// up
		tilePosition.y--;
		break;
	case eDirection::DOWN:	// down
		tilePosition.y++;
		break;
	}
	return tilePosition;
}

eDirection GetDirection(TilePosition to, TilePosition from)
{
	if (from.x < to.x)
	{
		return eDirection::RIGHT;
	}
	if (to.x < from.x)
	{
		return eDirection::LEFT;
	}
	if (from.y < to.y)
	{
		return eDirection::DOWN;
	}
	if (to.y < from.y)
	{
		return eDirection::UP;
	}

	return eDirection::NONE;
}