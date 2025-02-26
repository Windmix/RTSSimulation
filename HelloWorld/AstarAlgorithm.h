#pragma once
#include <unordered_set>
#include <memory>
#include <queue>
#include "CompareGameObjectX.h"
#include "PlayerMap.h"



class AstartAlgorithm
{
	bool containsInOpenList(std::shared_ptr<GameObjectX>& gameobject);
public:
	//storage
	std::priority_queue<std::shared_ptr<GameObjectX>, std::vector<std::shared_ptr<GameObjectX>>, CompareGameObjectX> openList;
	std::unordered_set<std::shared_ptr<GameObjectX>> closedList;
	std::unordered_set<std::shared_ptr<GameObjectX>> openSet;

	//singleton instance
	static std::shared_ptr<AstartAlgorithm> Instance();

	//methods
	std::vector<std::shared_ptr<GameObjectX>> findPath(std::shared_ptr<GameObjectX> start, std::shared_ptr<GameObjectX> end, std::shared_ptr<PlayerMap> map, bool isScoutUsing);
	int getDistance(std::shared_ptr<GameObjectX>& objectA, std::shared_ptr<GameObjectX>& objectB);
	std::vector<std::shared_ptr<GameObjectX>> retracePath(std::shared_ptr<GameObjectX>& startObject, std::shared_ptr<GameObjectX>& endObject);
};

