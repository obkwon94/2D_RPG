#include "LifeNPC.h"

LifeNPC::LifeNPC(std::wstring name, std::wstring scriptName, std::wstring textureFileName) :
	Character(name, scriptName, textureFileName)
{
	_type = eComponentType::CT_NPC;
}

LifeNPC::~LifeNPC()
{

}

void LifeNPC::UpdateAI(float deltaTime)
{

}