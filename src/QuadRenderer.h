#pragma once
#include "Renderer.h"
#include "QuadVertex.h"
#include <vector>
#include "ResourceManager.h"
#include <sstream>

class Texture;
class QuadRenderer : public Renderer
{
public:
	QuadRenderer(ShaderProgram* shader, int batchSize);

	~QuadRenderer();
	QuadRenderer(const QuadRenderer& other) = delete;
	QuadRenderer& operator=(const QuadRenderer& other) = delete;
	QuadRenderer(const QuadRenderer&& other) = delete;
	QuadRenderer& operator=(const QuadRenderer&& other) = delete;

public:
#pragma region Override functions
	virtual void Begin(Camera* camera) override;
	virtual void Flush() override;
	virtual void BeginBatch() override;
	virtual void NextBatch() override;
	virtual void End() override;
#pragma endregion

public:
	void DrawQuad(const glm::mat4& transform, Texture* texture, const glm::vec4& tintColor, bool flipped = false);
	void DrawQuad(const glm::vec3& position, Texture* texture, const glm::vec4& tintColor, bool flipped = false);
	void DrawQuad(const glm::mat4& transform, const glm::vec4& tintColor);
	void DrawQuad(const glm::vec3& position, const glm::vec4& tintColor);
private:
	int maxVertices = 0;
	int maxIndices = 0;
	const int maxTextureSlots = 32;

	std::vector<QuadVertex> vertices;
	std::vector<unsigned short> indices;
	
	int selectedTexture = 0;
	std::vector<Texture*> textureSlots;
	int textureSlotIndex = 0;
	int indexCount = 0;
	int vertexCount = 0;

	Texture* whiteTexture;

	glm::vec4 quadPositions[4] = {
	{-0.5f, 0.5f, 0, 1.0f},
	{0.5f, 0.5f, 0, 1.0f},
	{-0.5f, -0.5f, 0, 1.0f},
	{0.5f, -0.5f, 0, 1.0f}
	};

	glm::vec2 quadUvs[4] = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};
};

