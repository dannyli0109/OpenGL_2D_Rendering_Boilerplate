#pragma once
#include "Layer.h"
#include "LineRenderer.h";
#include "FrameBuffer.h"
#include "QuadRenderer.h"
#include "SceneWindow.h"
#include "Camera.h"

class SceneLayer :
	public Layer
{
public:
	SceneLayer();
	~SceneLayer();
	virtual void OnAttach() override;
	virtual void OnUpdate(float deltaTime) override;
	virtual void OnDetach() override;
private:
	virtual void OnMouseMove(glm::vec2 mousePos);
	virtual void OnMouseScroll(glm::vec2 mouseOff);
	LineRenderer* lineRenderer;
	FrameBuffer* frameBuffer;
	QuadRenderer* quadRenderer;

	ShaderProgram* lineShader;
	ShaderProgram* quadShader;
	ShaderProgram* frameBufferShader;

	const int gridLimits = 10;

	SceneWindow* sceneWindow;
	Camera* camera;

	bool coldStart = true;
};

