#include "ComponentSystem.h"
#include "Component.h"

Component::Component(std::wstring name)
{
	_type = eComponentType::CT_NONE;
	_name = name;
	ComponentSystem::GetInstance()->AddComponent(_name, this);
	_canMove = false;
	_isLive = true;

	_moveDistancePerTimeX = 0.0f;
	_moveDistancePerTimeY = 0.0f;
}

Component::~Component()
{

}

void Component::ReceiveMessage(const sComponentMsgParam& msgParam)
{
	if (L"Collision" == msgParam.message)
	{

	}
}