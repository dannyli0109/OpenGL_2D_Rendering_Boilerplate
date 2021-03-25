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

void ResourceManager::AddShader(ShaderProgram* shader)
{
	shaders.push_back(shader);
}

ShaderProgram* ResourceManager::GetShader(int key)
{
	if (key < 0 || key > shaders.size() - 1) return nullptr;
	return shaders[key];
}

void ResourceManager::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
}

Camera* ResourceManager::GetCamera(int key)
{
	if (key < 0 || key > cameras.size() - 1) return nullptr;
	return cameras[key];
}

void ResourceManager::AddWindow(Window* window)
{
	windows.push_back(window);
}

Window* ResourceManager::GetWindow(int key)
{
	if (key < 0 || key > windows.size() - 1) return nullptr;
	return windows[key];
}

Texture* ResourceManager::GetTexture(int key)
{
	if (key < 0 || key > textures.size() - 1) return nullptr;
	return textures[key];
}

void ResourceManager::Destroy()
{
	for (int i = 0; i < instance->textures.size(); i++)
	{
		delete instance->textures[i];
	}
	instance->textures.clear();

	for (int i = 0; i < instance->shaders.size(); i++)
	{
		delete instance->shaders[i];
	}
	instance->shaders.clear();

	for (int i = 0; i < instance->cameras.size(); i++)
	{
		delete instance->cameras[i];
	}
	instance->cameras.clear();

	for (int i = 0; i < instance->windows.size(); i++)
	{
		delete instance->windows[i];
	}
	instance->windows.clear();

	delete instance;
	instance = nullptr;
}
ResourceManager* ResourceManager::instance = nullptr;
