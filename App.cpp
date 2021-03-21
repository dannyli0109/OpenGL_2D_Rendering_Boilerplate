#include "App.h"

App::App()
{
	layerStack->PushLayer(new SceneLayer());
	layerStack->PushOverlay(new ConsoleLayer());
}
