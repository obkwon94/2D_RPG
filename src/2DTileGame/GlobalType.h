#pragma once

enum eDirection
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE,
};

typedef struct TilePosition
{
	int x;
	int y;
};

TilePosition GetNextTilePosition(TilePosition currentTilePos, eDirection direction);
