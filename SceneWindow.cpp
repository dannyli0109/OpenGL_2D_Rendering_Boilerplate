#include "SceneWindow.h"
#include "FrameBuffer.h"
#include "Window.h"
#include "Console.h"

SceneWindow::SceneWindow(std::string name, FrameBuffer* frameBuffer, Camera* camera)
{
	this->name = name;
	this->frameBuffer = frameBuffer;
	this->camera = camera;
}

void SceneWindow::Begin()
{
	ImGui::Begin(name.c_str());
	windowPos = ImGui::GetWindowContentRegionMin();
	if (ShouldUpdateSize())
	{
		glViewport(0, 0, windowSize.x, windowSize.y);
		frameBuffer->Create(windowSize.x, windowSize.y);
		camera->SetWindowSize({ windowSize.x, windowSize.y });
	}
}

bool SceneWindow::ShouldUpdateSize()
{
	ImVec2 size = ImGui::GetContentRegionAvail();
	if (size.x != windowSize.x || size.y != windowSize.y)
	{
		windowSize = size;
		return true;
	}
	return false;
}

void SceneWindow::Draw()
{
	ImGui::Image((ImTextureID)frameBuffer->GetTextureID(), { windowSize.x, windowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
}

void SceneWindow::End()
{
	ImGui::End();
}

