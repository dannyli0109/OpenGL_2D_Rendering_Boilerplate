#include "LineRenderer.h"


LineRenderer::LineRenderer(ShaderProgram* shader, int batchSize)
{
	this->shader = shader;
	maxVertices = batchSize * 2;

	vertices.resize(maxVertices);

	vertexBuffer = new VertexBuffer(maxVertices, sizeof(LineVertex));
	vertexArrayObject = new VertexArrayObject();

	vertexArrayObject->Bind();
	vertexBuffer->Bind();
	vertexBuffer->SetAttributePointers(
		{
			{3, GL_FLOAT, sizeof(LineVertex), (const void*)offsetof(LineVertex, LineVertex::position)},
			{4, GL_FLOAT, sizeof(LineVertex), (const void*)offsetof(LineVertex, LineVertex::color)}
		}
	);

	VertexArrayObject::Unbind();
	VertexBuffer::Unbind();
}

LineRenderer::~LineRenderer()
{
	delete vertexBuffer;
	delete vertexArrayObject;
}

void LineRenderer::Begin(Camera* camera)
{
	shader->UseShader();
	shader->SetUniform("u_ProjectionMatrix", camera->GetProjection());
	BeginBatch();
}


void LineRenderer::Flush()
{
	if (vertexCount == 0) return;
	vertexBuffer->SetData(vertices.data(), sizeof(LineVertex), vertexCount);

	vertexArrayObject->Bind();
	glDrawArrays(GL_LINES, 0, vertexCount);
	VertexArrayObject::Unbind();
	VertexBuffer::Unbind();
}

void LineRenderer::BeginBatch()
{
	vertices.resize(maxVertices);
	vertexCount = 0;
}

void LineRenderer::NextBatch()
{
	Flush();
	BeginBatch();
}

void LineRenderer::End()
{
	Flush();
}

void LineRenderer::DrawLine(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color)
{
	if (vertexCount >= maxVertices) NextBatch();

	vertices[vertexCount].position = p1;
	vertices[vertexCount].color = color;
	vertices[vertexCount + 1].position = p2;
	vertices[vertexCount + 1].color = color;
	
	vertexCount += 2;
}
