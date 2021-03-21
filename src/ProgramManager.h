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
#include "SceneWindow.h"
#include "EventManager.h"
#include "Event.h"
#include "LayerStack.h"

class ProgramManager
{
public:
	ProgramManager();
	bool IsRunning();
	void Run();
	void Destory();

	void OnEvent(Event* eventTriggerred)
	{
		
		// eventTriggerred;
		//*console << eventTriggerred->GetInfo() << true;
	}

private:
	void Begin();
	void Update(float deltaTime);
	void DrawGUI();
	void End();
protected:
	float time = 0.0f;
	Window* window;
	ImGuiContainer* imguiContainer;
	Console* console;
	ResourceManager* resourceManager;
	EventManager* eventManager;
	LayerStack* layerStack;
};


//LineRenderer* lineRenderer;

//QuadMesh* quadMesh;
//FrameBuffer* frameBuffer;
//QuadRenderer* quadRenderer;

//ShaderProgram* lineShader;
//ShaderProgram* quadShader;
//ShaderProgram* frameBufferShader;

//const int gridLimits = 10;

//ImVec2 sceneViewSize;
//SceneWindow* sceneWindow;