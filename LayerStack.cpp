#include "LayerStack.h"

LayerStack::LayerStack()
{
	layerInsert = layers.begin();
}

LayerStack::~LayerStack()
{
	for (Layer* layer : layers)
	{
		delete layer;
	}
}

void LayerStack::PushLayer(Layer* layer)
{
	layers.emplace(layerInsert, layer);
	layer->OnAttach();
}

void LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(layers.begin(), layers.end(), layer);
	if (it != layers.end())
	{
		layers.erase(it);
		layerInsert--;
		layer->OnDetach();
	}
}

void LayerStack::PushOverlay(Layer* overlay)
{
	layers.emplace_back(overlay);
	overlay->OnAttach();
}

void LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(layers.begin(), layers.end(), overlay);
	if (it != layers.end())
	{
		layers.erase(it);
		overlay->OnDetach();
	}
}
