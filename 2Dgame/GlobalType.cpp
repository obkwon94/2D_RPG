#include "GlobalType.h"

TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction)
{
	TilePosition tilePosition = currentTilePos;
	switch (direction)
	{
	case eDirection::LEFT:			//left
		tilePosition.x--;
		break;

	case eDirection::RIGHT:			//right
		tilePosition.x++;
		break;

	case eDirection::UP:			//up
		tilePosition.y--;
		break;

	case eDirection::DOWN:			//down
		tilePosition.y++;
		break;
	}
	return tilePosition;
}