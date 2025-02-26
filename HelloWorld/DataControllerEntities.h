#pragma once
#include"Worker.h"
#include"Scout.h"
#include"Builder.h"
#include"CoalMiner.h"
class DataControllerEntities
{
public:

	int WoodConsumtionCounter = 0;

	static std::shared_ptr<DataControllerEntities> instance();
	std::vector<std::shared_ptr<Worker>> TotalWorkers;
	std::vector<std::shared_ptr<Scout>> totalScouts;
	std::vector<std::shared_ptr<Builder>> TotalBuilders;
	std::vector<std::shared_ptr<CoalMiner>> TotalCoalMiners;

	int getInventoryWoodforAllWorkers();
	void woodConsumeFromAllworkersBuilding(int BuildingCost);
};    
 