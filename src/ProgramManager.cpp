#include "ProgramManager.h"

#pragma region Init
ProgramManager::ProgramManager()
{
	eventManager = EventManager::CreateInstance(this);

	window = Window::CreateInstance();
	window->Init(1920, 1010, "Window");

	// create console with size 100
	// meaning it displays the last 100 messages
	console = Console::CreateInstance(100);

#pragma region Load Resources
	resourceManager = ResourceManager::CreateInstance();
	resourceManager->AddTexture(new Texture("white.png"));
#pragma endregion

	imguiContainer = new ImGuiContainer();
	imguiContainer->Init();

	layerStack = new LayerStack();
}


#pragma region Run
void ProgramManager::Run()
{
	float deltaTime = window->GetTime() - time;
	time += deltaTime;
	Begin();
	Update(deltaTime);
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
	for (Layer* layer : *layerStack)
	{
		layer->OnUpdate(deltaTime);
	}
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
	Window::Destroy();
	Console::Destroy();
	ResourceManager::Destroy();
	EventManager::Destroy();
	delete imguiContainer;
	delete layerStack;
}
#pragma endregion
