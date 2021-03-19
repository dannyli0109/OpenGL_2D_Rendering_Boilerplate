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
	quadMesh = new QuadMesh();
	frameBuffer = new FrameBuffer(windowSize.x, windowSize.y);

	lineShader = new ShaderProgram("Line.vert", "Line.frag");
	quadShader = new ShaderProgram("Quad.vert", "Quad.frag");
	frameBufferShader = new ShaderProgram("FrameBuffer.vert", "FrameBuffer.frag");

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	lineRenderer = new LineRenderer(lineShader, 8192);
	quadRenderer = new QuadRenderer(quadShader, 8192);

	camera = new Camera({ 0, 0 }, 32.0f, windowSize);

	imguiContainer = new ImGuiContainer();
	imguiContainer->Init(window);
}
#pragma endregion

#pragma region Run
void ProgramManager::Run()
{
	while (window->Running())
	{
		float deltaTime = window->GetTime() - time;
		time += deltaTime;
		Begin();
		Update(deltaTime);
		Draw();
		End();
	}
	window->Destroy();
}
#pragma endregion

#pragma region Begin
void ProgramManager::Begin()
{
	imguiContainer->Begin();
}
#pragma endregion

#pragma region Update
void ProgramManager::Update(float deltaTime)
{
	if (window->ShouldUpdateSize())
	{
		glm::vec2 size = window->GetSize();
		glViewport(0, 0, size.x, size.y);
		frameBuffer->Create(size.x, size.y);
	}
}
#pragma endregion

#pragma region Draw
void ProgramManager::Draw()
{
	frameBuffer->Bind();
	glClearColor(0.2, 0.2, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	lineRenderer->Begin(camera);
	for (int i = 0; i < 10; i++)
	{
		lineRenderer->DrawLine({ i, 0, 1 }, { i, 5, 1 }, { 1, 0, 0, 1 });
	}
	lineRenderer->End();
	FrameBuffer::Unbind();

	glClear(GL_COLOR_BUFFER_BIT);

	DrawGUI();
}
#pragma endregion

#pragma region DrawGUI
void ProgramManager::DrawGUI()
{
	ImGui::Begin("GameWindow");
	{
		ImGui::BeginChild("GameRender");
		ImVec2 wsize = ImGui::GetWindowSize();
		ImGui::Image((ImTextureID)frameBuffer->GetTextureID(), wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();
	}
	ImGui::End();

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

	delete camera;
	delete imguiContainer;
	Console::Destroy();
}
#pragma endregion
