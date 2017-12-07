#pragma once

#include "StageParts.h"

class PathfinderStageLoader : public StageParts
{
public:
	PathfinderStageLoader(Stage* stage);
	~PathfinderStageLoader();

public:
	void CreateComponents(std::wstring mapName);
};