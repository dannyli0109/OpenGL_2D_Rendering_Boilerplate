#pragma once
#include "Window.h"
#include "ImGuiContainer.h"
#include "Debug.h"
#include "Console.h"
#include "ShaderProgram.h"
#include "Graphics.h"
#include "LineVertex.h"
#include "Camera.h"
#include "LineRenderer.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "QuadRenderer.h"
#include "FrameBuffer.h"
#include "QuadMesh.h"
//#include "FrameBufferVertex.h"
//#include "Mesh.h"

class ProgramManager
{
public:
	ProgramManager() = default;
	bool Init();
	void Run();
	void Destory();
private:
	void Begin();
	void Update(float deltaTime);
	void Draw();
	void DrawGUI();
	void End();
private:
	float time = 0.0f;
private:
	Window* window;
	ImGuiContainer* imguiContainer;
	Console* console;

	Camera* camera;
	ResourceManager* resourceManager;

	LineRenderer* lineRenderer;

	QuadMesh* quadMesh;
	FrameBuffer* frameBuffer;
	QuadRenderer* quadRenderer;

	ShaderProgram* lineShader;
	ShaderProgram* quadShader;
	ShaderProgram* frameBufferShader
};
