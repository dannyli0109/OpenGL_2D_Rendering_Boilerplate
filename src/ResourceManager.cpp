#include "ResourceManager.h"

ResourceManager* ResourceManager::GetInstance()
{
	return instance;
}

ResourceManager* ResourceManager::CreateInstance()
{
	if (!instance)
	{
		instance = new ResourceManager();
	}
	return instance;
}

void ResourceManager::AddTexture(Texture* texture)
{
	textures.push_back(texture);
}

Texture* ResourceManager::GetTexture(TextureKey key)
{
	int index = int(key);
	if (index < 0 || index > textures.size() - 1) return nullptr;
	return textures[index];
}

void ResourceManager::Destroy()
{
	for (int i = 0; i < instance->textures.size(); i++)
	{
		delete instance->textures[i];
	}
	instance->textures.clear();
	delete instance;
	instance = nullptr;
}
ResourceManager* ResourceManager::instance = nullptr;
