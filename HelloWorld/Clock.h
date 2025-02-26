#pragma once
#include <memory>

class Clock
{
public:
	float time;
	Clock();

	static std::shared_ptr<Clock> instance();

};