#pragma once
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "VertexAttribute.h"
#include <vector>
class Mesh
{
public:
	Mesh(unsigned int vertexCount, GLsizeiptr size, const void* vertices, std::vector<VertexAttribute> vertexAttributes, unsigned int indexCount, unsigned short* indices);
#pragma region Rule of Five
	virtual ~Mesh();
	Mesh(const Mesh& other) = delete;
	Mesh& operator=(const Mesh& other) = delete;
	Mesh(const Mesh&& other) = delete;
	Mesh& operator=(const Mesh&& other) = delete;
#pragma endregion

	virtual void Bind();
	static void Unbind();
	virtual void Draw();
protected:
	Mesh() {};
	void CreateMesh(unsigned int vertexCount, GLsizeiptr size, const void* vertices, std::vector<VertexAttribute> vertexAttributes, unsigned int indexCount, unsigned short* indices);
protected:
	VertexBuffer* vertexBuffer = nullptr;
	IndexBuffer* indexBuffer = nullptr;
	VertexArrayObject* vertexArrayObject = nullptr;
	int indexCount = 0;
	float width;
	float height;
};

