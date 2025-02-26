#include "CompareGameObjectX.h"

bool CompareGameObjectX::operator()(std::shared_ptr<GameObjectX>& a, std::shared_ptr<GameObjectX>& b)
{
	return a->getFcost() > b->getFcost();
}
