#pragma once
#include "Graphics.h"

class IndexBuffer
{
public:
	IndexBuffer(unsigned int indexCount, unsigned short* incides);
	void Bind();
	static void Unbind();
	
#pragma region Rule of Five
	~IndexBuffer();
	IndexBuffer(const IndexBuffer& other) = delete;
	IndexBuffer& operator=(const IndexBuffer& other) = delete;
	IndexBuffer(const IndexBuffer&& other) = delete;
	IndexBuffer& operator=(const IndexBuffer&& other) = delete;
#pragma endregion

private:
	GLuint id;
	bool initialised;
};

