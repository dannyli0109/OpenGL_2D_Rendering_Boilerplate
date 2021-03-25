#pragma once
#include <vector>

class Texture;
class ShaderProgram;
class Camera;
class Window;
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
	Texture* GetTexture(int key);
	void AddShader(ShaderProgram* shader);
	ShaderProgram* GetShader(int key);
	void AddCamera(Camera* camera);
	Camera* GetCamera(int key);
	void AddWindow(Window* window);
	Window* GetWindow(int key);
	
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
	std::vector<ShaderProgram*> shaders;
	std::vector<Camera*> cameras;
	std::vector<Window*> windows;
};

