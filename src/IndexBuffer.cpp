#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(unsigned int indexCount, unsigned short* incides)
{
	if (initialised)
	{
		glDeleteBuffers(1, &id);
	}
	initialised = true;

	glGenBuffers(1, &id);

	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(unsigned short), incides, GL_STATIC_DRAW);
	Unbind();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
	if (initialised)
	{
		glDeleteBuffers(1, &id);
		initialised = false;
	}
}
