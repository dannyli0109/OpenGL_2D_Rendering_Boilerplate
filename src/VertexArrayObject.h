#pragma once
#include "Graphics.h"
class VertexArrayObject
{
public:
	VertexArrayObject();

	~VertexArrayObject();
	VertexArrayObject(const VertexArrayObject& other) = delete;
	VertexArrayObject& operator=(const VertexArrayObject& other) = delete;
	VertexArrayObject(const VertexArrayObject&& other) = delete;
	VertexArrayObject& operator=(const VertexArrayObject&& other) = delete;

public:
	void Bind();
	static void Unbind();
private:
	GLuint id;
	bool initialised = false;
};

