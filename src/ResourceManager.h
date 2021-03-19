#pragma once
#include <vector>

class Texture;
enum class TextureKey
{
	white = 0
};

class ResourceManager
{
public:
	static ResourceManager* GetInstance();
	static ResourceManager* CreateInstance();
	void AddTexture(Texture* texture);
	Texture* GetTexture(TextureKey key);
	
	static void Destroy();
private:
	ResourceManager() {};

#pragma region Rule of Five
	~ResourceManager() {};
	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator=(const ResourceManager& other) = delete;
	ResourceManager(const ResourceManager&& other) = delete;
	ResourceManager& operator=(const ResourceManager&& other) = delete;
#pragma endregion

	static ResourceManager* instance;
	std::vector<Texture*> textures;

};

