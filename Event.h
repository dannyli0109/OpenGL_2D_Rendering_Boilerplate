#pragma once
#include <string>

class Event
{
public:
	Event() = default;
	virtual ~Event() {};
	bool handled = false;
};

