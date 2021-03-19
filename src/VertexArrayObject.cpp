#include "VertexArrayObject.h"

VertexArrayObject::VertexArrayObject()
{
	glGenVertexArrays(1, &id);
}

VertexArrayObject::~VertexArrayObject()
{
	glDeleteVertexArrays(1, &id);
}

void VertexArrayObject::Bind()
{
	glBindVertexArray(id);
}

void VertexArrayObject::Unbind()
{
	glBindVertexArray(0);
}
