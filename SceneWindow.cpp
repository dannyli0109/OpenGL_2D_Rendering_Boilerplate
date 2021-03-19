#include "SceneWindow.h"
#include "FrameBuffer.h"
#include "Window.h"
#include "Console.h"

SceneWindow::SceneWindow(std::string name, FrameBuffer* frameBuffer, Camera* camera, Window* window)
{
	this->name = name;
	this->frameBuffer = frameBuffer;
	this->camera = camera;
	this->window = window;
}

void SceneWindow::Begin()
{
	ImGui::Begin(name.c_str());
	windowSize = ImGui::GetContentRegionAvail();
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
	ImGui::Image((ImTextureID)frameBuffer->GetTextureID(), { windowSize.x, windowSize.y }, ImVec2(0, 1), ImVec2(1, 0));
}

void SceneWindow::End()
{
	ImGui::End();
}

glm::vec2 SceneWindow::GetCursorPos()
{
	glm::mat4 deprojection = glm::inverse(camera->GetProjection());
	double cursorX, cursorY;
	glfwGetCursorPos(window->Get(), &cursorX, &cursorY);

	ImVec2 pos = ImGui::GetWindowContentRegionMin();
	
	cursorX -= pos.x;
	cursorY -= pos.y;

	cursorX = (cursorX / windowSize.x) * 2 - 1;
	cursorY = -((cursorY / windowSize.y) * 2 - 1);

	glm::vec4 mousePosNDC(float(cursorX), float(cursorY), 0, 1);
	glm::vec4 mousePosWorld = deprojection * mousePosNDC;

	glm::vec2 mousePos = { 0, 0 };
	mousePos.x = mousePosWorld.x;
	mousePos.y = mousePosWorld.y;
	return mousePos;
}
