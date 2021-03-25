#include "Renderer2D.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Window.h"
#include "LineRenderer.h"
#include "QuadRenderer.h"
#include "ShaderProgram.h"
#include "Texture.h"
#include "Graphics.h"

namespace Renderer2D
{
	void Init(Settings settings)
	{
		Manager::CreateInstance(settings);
	}

	void Init()
	{
		Manager::CreateInstance();
	}

	void InitRenderer()
	{
		Manager* manager = Manager::GetInstance();
		manager->resourceManager->AddTexture(new Texture("white.png"));
		manager->resourceManager->AddShader(new ShaderProgram("Line.vert", "Line.frag"));
		manager->resourceManager->AddShader(new ShaderProgram("Quad.vert", "Quad.frag"));

		manager->lineRenderer = new LineRenderer(manager->resourceManager->GetShader(0), manager->settings.batchSize);
		manager->quadRenderer = new QuadRenderer(manager->resourceManager->GetShader(1), manager->settings.batchSize);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void InitWindow(int width, int height, std::string title)
	{
		Window* window = new Window(width, height, title);
		Manager* manager = Manager::GetInstance();
		manager->resourceManager->AddWindow(window);
		if (!manager->window)
		{
			manager->window = window;
		}
	}

	bool WindowRunning()
	{
		return Manager::GetInstance()->window->Running();
	}

	void UpdateWindow()
	{
		Manager::GetInstance()->window->Update();
	}

	void ViewPort(float x, float y, float width, float height)
	{
		glViewport(x, y, width, height);
	}

	void InitCamera(glm::vec2 center, glm::vec2 size, float zoom)
	{
		Camera* camera = new Camera(center, size, zoom);
		Manager* manager = Manager::GetInstance();
		manager->resourceManager->AddCamera(camera);
		if (!manager->camera)
		{
			manager->camera = camera;
		}
	}

	void LoadTexture(std::string filePath)
	{
		Manager::GetInstance()->resourceManager->AddTexture(new Texture(filePath));
	}

	Texture* GetTextrue(int index)
	{
		return ResourceManager::GetInstance()->GetTexture(index);
	}

	void LoadShader(std::string vertexShaderPath, std::string fragmentShaderPath)
	{
		ResourceManager::GetInstance()->AddShader(new ShaderProgram(vertexShaderPath, fragmentShaderPath));
	}

	ShaderProgram* GetShader(int index)
	{
		return ResourceManager::GetInstance()->GetShader(index);
	}

	void UseCamera(int index)
	{
		Manager* manager = Manager::GetInstance();
		manager->camera = manager->resourceManager->GetCamera(index);
	}

	void UseWindow(int index)
	{
		Manager* manager = Manager::GetInstance();
		manager->window = manager->resourceManager->GetWindow(index);
	}

	void Begin()
	{
		Manager* manager = Manager::GetInstance();
		if (manager->renderer && manager->camera)
		{
			manager->renderer->Begin(manager->camera);
		}
	}

	void End()
	{
		if (Manager::GetInstance()->renderer)
		{
			Manager::GetInstance()->renderer->End();
		}
		Manager::GetInstance()->renderer = nullptr;
	}

	void BackgroundColor(glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.b);
	}

	void Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Clear(int mask)
	{
		glClear(mask);
	}

	void Color(glm::vec4 color)
	{
		Manager::GetInstance()->settings.color = color;
	}

	void LayerOrder(int layerOrder)
	{
		Manager::GetInstance()->settings.layerOrder = layerOrder;
	}

	void DrawLine(glm::vec2 p1, glm::vec2 p2)
	{
		Manager* manager = Manager::GetInstance();
		manager->UseLineRenderer();
		manager->lineRenderer->DrawLine(glm::vec3(p1, -manager->settings.layerOrder), glm::vec3(p2, -manager->settings.layerOrder), manager->settings.color);
	}

	void DrawCircle(glm::vec2 center, float radius)
	{
		Manager* manager = Manager::GetInstance();
		manager->UseLineRenderer();
		manager->lineRenderer->DrawCircle(glm::vec3(center, manager->settings.layerOrder), radius, manager->settings.color, manager->settings.circleSegments);
	}
	void Destroy()
	{
		Manager::GetInstance()->Destroy();
	}
}

namespace Renderer2D
{
	Manager* Manager::CreateInstance(Settings settings)
	{
		if (!instance)
		{
			instance = new Manager(settings);
		}
		return instance;
	}

	Manager* Manager::CreateInstance()
	{
		if (!instance)
		{
			instance = new Manager();
		}
		return instance;
	}

	Manager* Manager::GetInstance()
	{
		return instance;
	}

	void Manager::Destroy()
	{
		delete instance;
		instance = nullptr;
	}

	void Manager::UseQuadRenderer()
	{
		if (renderer != quadRenderer)
		{
			if (renderer)
			{
				renderer->End();
			}
			renderer = quadRenderer;
			renderer->Begin(camera);
		}
	}

	void Manager::UseLineRenderer()
	{
		if (renderer != lineRenderer)
		{
			if (renderer)
			{
				renderer->End();
			}
			renderer = lineRenderer;
			renderer->Begin(camera);
		}
	}

	Manager::Manager(Settings settings)
	{
		this->settings = settings;
		Init();
	}

	Manager::Manager()
	{
		Init();
	}

	void Manager::Init()
	{
		resourceManager = ResourceManager::CreateInstance();
	}

	Manager::~Manager()
	{
		ResourceManager::Destroy();

		delete lineRenderer;
		delete quadRenderer;
	}

	Manager* Manager::instance = nullptr;

}
