#pragma once

class Camera;
class ShaderProgram;
class VertexBuffer;
class VertexArrayObject;
class IndexBuffer;

class Renderer
{
public:
	virtual void Begin(Camera* camera) = 0;
	virtual void Flush() = 0;
	virtual void BeginBatch() = 0;
	virtual void NextBatch() = 0;
	virtual void End() = 0;

protected:
	ShaderProgram* shader;


	VertexBuffer* vertexBuffer;
	IndexBuffer* indexBuffer;
	VertexArrayObject* vertexArrayObject;

};

