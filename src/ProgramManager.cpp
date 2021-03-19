#include "ProgramManager.h"

#pragma region Init
bool ProgramManager::Init()
{
	window = new Window();

	if (!window->Init(1920, 1010, "Window")) return false;


	// create console with size 100
	// meaning it displays the last 100 messages
	console = Console::CreateInstance(100);

#pragma region Load Resources
	resourceManager = ResourceManager::CreateInstance();
	resourceManager->AddTexture(new Texture("white.png"));
#pragma endregion

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

	imguiContainer = new ImGuiContainer();
	imguiContainer->Init(window);

}
#pragma endregion

#pragma region Run
void ProgramManager::Run()
{
	float deltaTime = window->GetTime() - time;
	time += deltaTime;
	Begin();
	Update(deltaTime);
	Draw();
	End();
}
#pragma endregion

#pragma region Begin
void ProgramManager::Begin()
{
	imguiContainer->Begin();

}
#pragma endregion

bool ProgramManager::IsRunning()
{
	return window->Running();
}

#pragma region Update
void ProgramManager::Update(float deltaTime)
{

}
#pragma endregion

#pragma region Draw
void ProgramManager::Draw()
{

	sceneWindow->Begin();
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
	lineRenderer->End();
	FrameBuffer::Unbind();

	glClear(GL_COLOR_BUFFER_BIT);

	sceneWindow->Draw();
	sceneWindow->End();
	DrawGUI();
}
#pragma endregion

#pragma region DrawGUI
void ProgramManager::DrawGUI()
{	

	ImGui::Begin("Properties");

	ImGui::End();
	console->DrawGUI();
}
#pragma endregion

#pragma region End
void ProgramManager::End()
{
	imguiContainer->End();
	window->End();
}
#pragma endregion

#pragma region Destroy
void ProgramManager::Destory()
{
	delete window;
	delete lineShader;
	delete lineRenderer;

	delete frameBuffer;
	delete quadShader;
	delete quadRenderer;

	delete frameBufferShader;

	delete camera;
	delete imguiContainer;

	delete sceneWindow;
	Console::Destroy();
	resourceManager->Destroy();
}
#pragma endregion
