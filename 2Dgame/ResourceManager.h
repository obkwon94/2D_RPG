#pragma once
#include <windows.h>
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include "Texture.h"

class ResourceManager
{
	//Singleton
private:
	static ResourceManager* _instance;

public:
	static ResourceManager* GetInstance();

private:
	ResourceManager();
public:
	~ResourceManager();

	//ResourceManager
private:
	std::map<std::wstring, Texture*> _textureMap;
	std::map<std::wstring, std::vector<std::string>> _scriptMap;
public:
	Texture* LoadTexture(std::wstring textureFileName);
	std::vector<std::string> LoadScript(std::wstring scriptFileName);
};