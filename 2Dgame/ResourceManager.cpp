#include <stdio.h>

#include "ResourceManager.h"

ResourceManager* ResourceManager::_instance = NULL;

ResourceManager::ResourceManager()
{

}

ResourceManager::~ResourceManager()
{

}

ResourceManager* ResourceManager::GetInstance()
{
	if (NULL == _instance)
		_instance = new ResourceManager();

	return _instance;
}

Texture* ResourceManager::LoadTexture(std::wstring textureFileName)
{
	std::map<std::wstring, Texture*>::iterator it = _textureMap.find(textureFileName);
	if (it != _textureMap.end())
	{
		return it->second;
	}

	Texture* texture = new Texture();
	texture->Init(textureFileName.c_str());		

	_textureMap[textureFileName] = texture;

	return texture;
}

std::vector<std::string> ResourceManager::LoadScript(std::wstring scriptFileName)
{
	std::map<std::wstring, std::vector<std::string>>::iterator it = _scriptMap.find(scriptFileName);
	if (it != _scriptMap.end())
	{
		return it->second;
	}

	char record[1000];
	std::ifstream infile(scriptFileName);
	std::vector<std::string> scriptTextList;
	while (!infile.eof())
	{
		infile.getline(record, 100);
		scriptTextList.push_back(record);
	}

	_scriptMap[scriptFileName] = scriptTextList;

	return scriptTextList;
}