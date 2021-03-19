#pragma once
#include "Graphics.h"
struct VertexAttribute {
	GLint size;
	GLenum type;
	GLsizei stride;
	const void* pointer;
};