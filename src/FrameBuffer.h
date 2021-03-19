#pragma once
#include "Graphics.h"
#include "Console.h"

class FrameBuffer
{
public:
	FrameBuffer() = default;
	FrameBuffer(int width, int height);

#pragma region Rule of Five
	~FrameBuffer();
	FrameBuffer(const FrameBuffer& other) = delete;
	FrameBuffer& operator=(const FrameBuffer& other) = delete;
	FrameBuffer(const FrameBuffer&& other) = delete;
	FrameBuffer& operator=(const FrameBuffer&& other) = delete;
#pragma endregion

	void Create(int width, int height);
	void Bind();
	void BindTexture(int textureUnit = 0);
	static void Unbind();
	void Destroy();

#pragma region Getters
	GLuint GetTextureID() { return texID; }
#pragma endregion

private:
	GLuint fboID;
	GLuint texID;
	bool initialised;
};

