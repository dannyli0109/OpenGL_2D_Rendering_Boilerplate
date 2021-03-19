#include "QuadRenderer.h"
#include "Texture.h"
#include "ShaderProgram.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArrayObject.h"
#include "Camera.h"

QuadRenderer::QuadRenderer(ShaderProgram* shader, int batchSize)
{
	this->shader = shader;
	maxVertices = batchSize * 4;
	maxIndices = batchSize * 6;

	vertices.resize(maxVertices);
	indices.resize(maxIndices);
	textureSlots.resize(maxTextureSlots);
	
	whiteTexture = ResourceManager::GetInstance()->GetTexture(TextureKey::white);
	textureSlots[0] = whiteTexture;
	textureSlotIndex = 1;

	int offset = 0;
	for (int i = 0; i < maxIndices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 1;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 2;
		offset += 4;
	}

	for (int i = 0; i < maxTextureSlots; i++)
	{
		std::stringstream tex;
		tex << "u_Textures[" << i << "]";
		shader->SetUniform(tex.str(), i);
	}

	vertexBuffer = new VertexBuffer(maxVertices, sizeof(QuadVertex));
	indexBuffer = new IndexBuffer(maxIndices, indices.data());
	vertexArrayObject = new VertexArrayObject();

	vertexArrayObject->Bind();
	vertexBuffer->Bind();
	indexBuffer->Bind();

	vertexBuffer->SetAttributePointers(
		{
			{3, GL_FLOAT, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, QuadVertex::position)},
			{4, GL_FLOAT, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, QuadVertex::color)},
			{2, GL_FLOAT, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, QuadVertex::uv)},
			{1, GL_FLOAT, sizeof(QuadVertex), (const void*)offsetof(QuadVertex, QuadVertex::textureIndex)}
		}
	);

	VertexArrayObject::Unbind();
	VertexBuffer::Unbind();
	IndexBuffer::Unbind();
}

QuadRenderer::~QuadRenderer()
{
	delete vertexBuffer;
	delete indexBuffer;
	delete vertexArrayObject;
}

void QuadRenderer::Begin(Camera* camera)
{
	shader->UseShader();
	shader->SetUniform("u_ProjectionMatrix", camera->GetProjection());
}

void QuadRenderer::Flush()
{
	if (indexCount == 0) return;
	vertexBuffer->SetData(vertices.data(), sizeof(QuadVertex), vertexCount);

	for (int i = 0; i < textureSlotIndex; i++)
	{
		textureSlots[i]->Bind(i);
	}

	vertexArrayObject->Bind();
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);

	VertexArrayObject::Unbind();
	VertexBuffer::Unbind();
	IndexBuffer::Unbind();
}

void QuadRenderer::BeginBatch()
{
	indexCount = 0;
	vertexCount = 0;
	vertices.resize(maxVertices);
	textureSlotIndex = 1;
}

void QuadRenderer::NextBatch()
{
	Flush();
	BeginBatch();
}

void QuadRenderer::End()
{
	Flush();
}

void QuadRenderer::DrawQuad(const glm::mat4& transform, Texture* texture, const glm::vec4& tintColor, bool flipped)
{
	if (indexCount >= maxIndices) NextBatch();

	float textureIndex = 0.0f;
	for (int i = 1; i < textureSlotIndex; i++)
	{
		if (*textureSlots[i] == *texture)
		{
			textureIndex = (float)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		if (textureSlotIndex >= maxTextureSlots)
			NextBatch();

		textureIndex = (float)textureSlotIndex;
		textureSlots[textureSlotIndex] = texture;
		textureSlotIndex++;
	}


	for (int i = 0; i < 4; i++)
	{
		vertices[vertexCount].position = transform * quadPositions[i];
		vertices[vertexCount].color = tintColor;
		vertices[vertexCount].uv = quadUvs[i];
		vertices[vertexCount].textureIndex = textureIndex;
		if (flipped)
		{
			vertices[vertexCount].uv.x = 1 - vertices[vertexCount].uv.x;
		}
		vertexCount++;
	}
	indexCount += 6;
}

void QuadRenderer::DrawQuad(const glm::vec3& position, Texture* texture, const glm::vec4& tintColor, bool flipped)
{
	glm::mat4 transform = glm::translate(glm::mat4(1), position);
	DrawQuad(transform, texture, tintColor, flipped);
}

void QuadRenderer::DrawQuad(const glm::mat4& transform, const glm::vec4& tintColor)
{
	if (indexCount >= maxIndices) NextBatch();
	int textureIndex = 0;

	for (int i = 0; i < 4; i++)
	{
		vertices[vertexCount].position = transform * quadPositions[i];
		vertices[vertexCount].color = tintColor;
		vertices[vertexCount].uv = quadUvs[i];
		vertices[vertexCount].textureIndex = textureIndex;
		vertexCount++;
	}
	indexCount += 6;
}

void QuadRenderer::DrawQuad(const glm::vec3& position, const glm::vec4& tintColor)
{
	glm::mat4 transform = glm::translate(glm::mat4(1), position);
	DrawQuad(transform, tintColor);
}
