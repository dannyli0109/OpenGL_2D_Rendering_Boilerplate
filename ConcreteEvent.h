#pragma once
#include <vector>
#include <map>
#include "Event.h"

template <typename Func, typename... Args>
class ConcreteEvent : public Event
{
public:
	ConcreteEvent() = default;
	virtual ~ConcreteEvent() {};
	virtual void Attach(void* obj, Func func) {
		listeners.insert({ obj, func });
	};

	virtual void Detach(void* obj)
	{
		listeners.erase(obj);
	}

	virtual void Notify(Args... args)
	{
		for (auto it = listeners.rbegin(); it != listeners.rend(); it++)
		{
			it->second(std::forward<Args>(args)...);
			if (handled) break;
		}
		handled = false;
	}

protected:
	std::map<void*, Func> listeners;
};