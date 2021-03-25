#pragma once
//#include "Graphics.h"
#include <string>
#include <vector>
#include "Matrices.h"

class Renderer;
class ResourceManager;
class Texture;
class ShaderProgram;
class Camera;
class LineRenderer;
class QuadRenderer;
class Window;

namespace Renderer2D {

	struct Settings
	{
		glm::vec4 color = { 0, 0, 0, 1 };
		int circleSegments = 64;
		int layerOrder = 0;
		int batchSize = 8192;
	};

	class Manager {
	public:
		static Manager* CreateInstance(Settings settings);
		static Manager* CreateInstance();
		static Manager* GetInstance();
		static void Destroy();
		void UseQuadRenderer();
		void UseLineRenderer();
		ResourceManager* resourceManager;
		LineRenderer* lineRenderer;
		QuadRenderer* quadRenderer;

		Camera* camera = nullptr;
		Window* window = nullptr;
		Renderer* renderer = nullptr;
		Settings settings;
	private:
		Manager(Settings settings);
		Manager();
		void Init();
		~Manager();
		static Manager* instance;
	};
}
	//const int DRAWMODE_LINE = 0;
	//const int DRAWMODE_COLOR = 1;

namespace Renderer2D
{ 
	void Init(Settings settings);
	void Init();
	void InitRenderer();
	void InitWindow(int width, int height, std::string title);
	bool WindowRunning();
	void UpdateWindow();
	void ViewPort(float x, float y, float width, float height);
	void InitCamera(glm::vec2 center, glm::vec2 size, float zoom);

	void LoadTexture(std::string filePath);
	Texture* GetTextrue(int index);
	void LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath);
	ShaderProgram* GetShader(int index);

	void UseCamera(int index);
	void UseWindow(int index);
	void Begin();
	void End();

	//void DrawMode(int drawMode);

	void BackgroundColor(glm::vec4 color);
	// Clear the color buffer by default
	void Clear();
	void Clear(int flags);

	void Color(glm::vec4 color);
	// Negative z position
	void LayerOrder(int layerOrder);
	void DrawLine(glm::vec2 p1, glm::vec2 p2);
	void DrawCircle(glm::vec2 center, float radius);

	void Destroy();
}
