#pragma once
#include"GameObjectX.h"
#include"memory.h"
#include<vector>
class DataControllerTrees
{
public:
	static std::shared_ptr<DataControllerTrees> instance();
	std::vector<std::shared_ptr<GameObjectX>> foundTrees;
};