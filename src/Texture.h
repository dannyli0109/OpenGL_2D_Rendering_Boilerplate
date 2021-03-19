#pragma once
#include "Graphics.h"
#include <string>
#include "Console.h"

class Texture
{
public:
	Texture(glm::vec2 size, unsigned char* data, int channels);
	Texture(std::string filename);

#pragma region Rule of Five
	~Texture();
	Texture(const Texture& other) = delete;
	Texture& operator=(const Texture& other) = delete;
	Texture(const Texture&& other) = delete;
	Texture& operator=(const Texture&& other) = delete;
#pragma endregion

	void Bind(int textureUnit);
	void Destroy();
	static void Unbind();
	bool operator==(const Texture& other);

private:
	void Create(glm::vec2 size, unsigned char* data, int channels);

private:
	GLuint id;
	bool initialised;
};

