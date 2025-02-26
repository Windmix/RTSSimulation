#pragma once
#include <memory>
#include "GameObjectX.h"
struct CompareGameObjectX
{
	bool operator()(std::shared_ptr<GameObjectX>& a, std::shared_ptr<GameObjectX>& b); // min heap behavior
};