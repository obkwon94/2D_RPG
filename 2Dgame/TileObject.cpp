#include "Sprite.h"
#include "TileObject.h"

TileObject::TileObject(std::wstring name, Sprite* sprite) : Component(name)
{
	_sprite = sprite;
}

TileObject::~TileObject()
{

}

void TileObject::Init()
{

}

void TileObject::DeInit()
{
	_sprite->DeInit();
}

void TileObject::Update(float deltaTime)
{
	_sprite->Update(deltaTime);
}

void TileObject::Render()
{
	_sprite->SetPosition(_posX, _posY);
	_sprite->Render();
}

void TileObject::Release()
{
	_sprite->Release();
}

void TileObject::Reset()
{
	_sprite->Reset();
}

void TileObject::SetPosition(float posX, float posY)
{
	_posX = posX;
	_posY = posY;
}

void TileObject::MoveDeltaPosition(float deltaX, float deltaY)
{
	_posX += deltaX;
	_posY += deltaY;
}