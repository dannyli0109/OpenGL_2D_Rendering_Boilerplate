#pragma once
#include "ShaderProgram.h"
#include "Graphics.h"
#include "LineVertex.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"
#include "Camera.h"
#include "Renderer.h"

class LineRenderer : public Renderer
{
public:
	LineRenderer(ShaderProgram* shader, int batchSize);

	~LineRenderer();
	LineRenderer(const LineRenderer& other) = delete;
	LineRenderer& operator=(const LineRenderer& other) = delete;
	LineRenderer(const LineRenderer&& other) = delete;
	LineRenderer& operator=(const LineRenderer&& other) = delete;

public:
#pragma region Override functions
	virtual void Begin(Camera* camera) override;
	virtual void Flush() override;
	virtual void BeginBatch() override;
	virtual void NextBatch() override;
	virtual void End() override;
#pragma endregion

public:
	void DrawLine(const glm::vec3& p1, const glm::vec3& p2, const glm::vec4& color);
	void DrawCircle(const glm::vec3& center, float size, const glm::vec4& color, int segmentCount);

private:
	std::vector<LineVertex> vertices;
	int maxVertices = 0;
	int vertexCount = 0;
};

