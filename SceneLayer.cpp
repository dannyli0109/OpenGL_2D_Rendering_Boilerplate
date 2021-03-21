#include "SceneLayer.h"
#include "Window.h"
#include "EventManager.h"

#define BIND_FUNC(x) std::bind(&SceneLayer::x, this, std::placeholders::_1)

SceneLayer::SceneLayer()
{
	Window* window = Window::GetInstance();
	EventManager* eventManager = EventManager::GetInstance();
	glm::vec2 windowSize = window->GetSize();

	frameBuffer = new FrameBuffer(windowSize.x, windowSize.y);

	lineShader = new ShaderProgram("Line.vert", "Line.frag");
	quadShader = new ShaderProgram("Quad.vert", "Quad.frag");
	frameBufferShader = new ShaderProgram("FrameBuffer.vert", "FrameBuffer.frag");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	lineRenderer = new LineRenderer(lineShader, 8192);
	quadRenderer = new QuadRenderer(quadShader, 8192);

	camera = new Camera({ 0, 0 }, 32.0f, windowSize);

	sceneWindow = new SceneWindow("GameWindow", frameBuffer, camera);
}

SceneLayer::~SceneLayer()
{
	delete lineRenderer;
	delete quadRenderer;
	delete frameBuffer;

	delete lineShader;
	delete quadShader;
	delete frameBufferShader;

	delete camera;
	delete sceneWindow;
}

void SceneLayer::OnAttach()
{
	EventManager::GetInstance()->onMouseMove->Attach(this, BIND_FUNC(OnMouseMove));
	EventManager::GetInstance()->onMouseScroll->Attach(this, BIND_FUNC(OnMouseScroll));
}

void SceneLayer::OnUpdate(float deltaTime)
{
	sceneWindow->Begin();
	// render the scene onto the frame buffer then render on to the scene window
	frameBuffer->Bind();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	lineRenderer->Begin(camera);
	for (float i = (float)-gridLimits; i <= (float)gridLimits; i++)
	{
		glm::vec4 colour = (i == 0) ? glm::vec4(0.8f, 0.8f, 0.8f, 1) : glm::vec4(0.3f, 0.3f, 0.3f, 1);
		lineRenderer->DrawLine({ i, -gridLimits, 0 }, { i, gridLimits, 0 }, colour);
		lineRenderer->DrawLine({ -gridLimits, i, 0 }, { gridLimits, i, 0 }, colour);
	}
	lineRenderer->DrawLine({ 0, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0, 1 });
	lineRenderer->DrawLine({ 0, 0, 0 }, { 0, 1, 0 }, { 0, 1, 0, 1 });

	glm::vec2 cursorPos = sceneWindow->GetCursorPos();

	lineRenderer->DrawCircle({ cursorPos.x, cursorPos.y, 0 }, 2, { 1, 0, 0, 1 }, 64);
	lineRenderer->End();
	FrameBuffer::Unbind();

	glClear(GL_COLOR_BUFFER_BIT);

	sceneWindow->Draw();
	sceneWindow->End();
}

void SceneLayer::OnDetach()
{
	EventManager::GetInstance()->onMouseMove->Detach(this);
	EventManager::GetInstance()->onMouseScroll->Detach(this);
}

void SceneLayer::OnMouseMove(glm::vec2 mousePos)
{
	glm::mat4 deprojection = glm::inverse(this->camera->GetProjection());

	glm::vec2 windowPos = sceneWindow->GetWindowPos();
	mousePos.x -= windowPos.x;
	mousePos.y -= windowPos.y;

	glm::vec2 windowSize = sceneWindow->GetWindowSize();
	mousePos.x = (mousePos.x / windowSize.x) * 2.0f - 1.0f;
	mousePos.y = -((mousePos.y / windowSize.y) * 2.0f - 1.0f);

	glm::vec4 mousePosNDC(mousePos, 0, 1);
	glm::vec4 mousePosWorld = deprojection * mousePosNDC;

	sceneWindow->SetCursorPos({ mousePosWorld.x, mousePosWorld.y });
}

void SceneLayer::OnMouseScroll(glm::vec2 mouseOff)
{
	camera->SetZoom(this->camera->GetZoom() + mouseOff.y * 2.0f);
}
