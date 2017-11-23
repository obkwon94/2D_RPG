#pragma once
#include <Windows.h>
#include "Component.h"

class Sprite;

class RecoveryItem : public Component
{
private:
	Sprite* _sprite;
	float _x;
	float _y;

	std::wstring _scriptFilename;
	std::wstring _textureFilename;

public:
	RecoveryItem(LPCWSTR name, LPCWSTR scriptFilename, LPCWSTR textureFilename);
	~RecoveryItem();

	void Init();
	void DeInit();
	void Update(float deltaTime);
	void Render();
	void Release();
	void Reset();

	void SetPosition(float posX, float posY);
	void MoveDeltaPosition(float deltaX, float deltaY);

	//message
	void ReceiveMessage(const sComponentMsgParam& msgParam);
};