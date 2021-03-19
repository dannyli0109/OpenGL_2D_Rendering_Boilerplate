#include "SceneWindow.h"
#include "FrameBuffer.h"

SceneWindow::SceneWindow(std::string name, FrameBuffer* frameBuffer, Camera* camera)
{
	this->name = name;
	this->frameBuffer = frameBuffer;
	this->camera = camera;
}

void SceneWindow::Begin()
{
	ImGui::Begin(name.c_str());
	ImGui::BeginChild("GameRender");
	if (ShouldUpdateSize())
	{
		glm::vec2 sceneWindowSize = GetSize();
		glViewport(0, 0, sceneWindowSize.x, sceneWindowSize.y);
		frameBuffer->Create(sceneWindowSize.x, sceneWindowSize.y);
		camera->SetWindowSize(sceneWindowSize);
	}
}

bool SceneWindow::ShouldUpdateSize()
{
	ImVec2 size = ImGui::GetWindowSize();
	if (size.x != width || size.y != height)
	{
		width = size.x;
		height = size.y;
		return true;
	}
	return false;
}

void SceneWindow::Draw()
{
	glm::vec2 sceneWindowSize = GetSize();
	ImGui::Image((ImTextureID)frameBuffer->GetTextureID(), { sceneWindowSize.x, sceneWindowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
}

void SceneWindow::End()
{
	ImGui::EndChild();
	ImGui::End();
}
