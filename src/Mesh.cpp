#include "Mesh.h"

Mesh::Mesh(unsigned int vertexCount, GLsizeiptr size, const void* vertices, std::vector<VertexAttribute> vertexAttributes, unsigned int indexCount, unsigned short* indices)
{
	CreateMesh(vertexCount, size, vertices, vertexAttributes, indexCount, indices);
}

void Mesh::CreateMesh(unsigned int vertexCount, GLsizeiptr size, const void* vertices, std::vector<VertexAttribute> vertexAttributes, unsigned int indexCount, unsigned short* indices)
{
	this->indexCount = indexCount;
	vertexBuffer = new VertexBuffer(vertexCount, size, vertices);
	indexBuffer = new IndexBuffer(indexCount, indices);
	vertexArrayObject = new VertexArrayObject();

	vertexArrayObject->Bind();
	vertexBuffer->Bind();
	indexBuffer->Bind();

	vertexBuffer->SetAttributePointers(vertexAttributes);

	VertexArrayObject::Unbind();
	VertexBuffer::Unbind();
	IndexBuffer::Unbind();
}

Mesh::~Mesh()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete vertexArrayObject;
}

void Mesh::Bind()
{
	vertexArrayObject->Bind();
}

void Mesh::Unbind()
{
	VertexArrayObject::Unbind();
	VertexBuffer::Unbind();
	IndexBuffer::Unbind();
}

void Mesh::Draw()
{
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);
}
