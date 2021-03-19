#pragma once
#include "Graphics.h"
#include <vector>
#include "VertexAttribute.h"

class VertexBuffer
{
public:
	VertexBuffer(unsigned int vertexCount, GLsizeiptr size);
	VertexBuffer(unsigned int vertexCount, GLsizeiptr size, const void* data);

	~VertexBuffer();
	VertexBuffer(const VertexBuffer& other) = delete;
	VertexBuffer& operator=(const VertexBuffer& other) = delete;
	VertexBuffer(const VertexBuffer&& other) = delete;
	VertexBuffer& operator=(const VertexBuffer&& other) = delete;

	void SetAttributePointers(std::vector<VertexAttribute> attributes);
	void Bind();
	static void Unbind();
	void SetData(const void* data, GLsizeiptr size, int vertexCount);

private:
	GLuint id;
	bool initialised = false;
};

