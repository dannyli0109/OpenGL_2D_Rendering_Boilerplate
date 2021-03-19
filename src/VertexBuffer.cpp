#include "VertexBuffer.h"

// dynamic draw
VertexBuffer::VertexBuffer(unsigned int vertexCount, GLsizeiptr size)
{
	if (initialised)
	{
		glDeleteBuffers(1, &id);
	}
	initialised = true;
	
	glGenBuffers(1, &id);

	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexCount * size, nullptr, GL_DYNAMIC_DRAW);
	Unbind();
}

// static draw
VertexBuffer::VertexBuffer(unsigned int vertexCount, GLsizeiptr size, const void* data)
{
	if (initialised)
	{
		glDeleteBuffers(1, &id);
	} 
	initialised = true;

	glGenBuffers(1, &id);
	Bind();
	glBufferData(GL_ARRAY_BUFFER, vertexCount * size, data, GL_STATIC_DRAW);
	Unbind();
}

VertexBuffer::~VertexBuffer()
{
	if (initialised)
	{
		glDeleteBuffers(1, &id);
	}
}

void VertexBuffer::SetAttributePointers(std::vector<VertexAttribute> attributes)
{
	for (int i = 0; i < attributes.size(); i++)
	{
		VertexAttribute attribute = attributes[i];
		glVertexAttribPointer(i, attribute.size, attribute.type, GL_FALSE, attribute.stride, attribute.pointer);
		glEnableVertexAttribArray(i);
	}
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetData(const void* data, GLsizeiptr size, int vertexCount)
{
	Bind();
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * size, data);
	Unbind();
}
