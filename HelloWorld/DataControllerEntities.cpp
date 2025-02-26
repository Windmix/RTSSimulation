#include "DataControllerEntities.h"

std::shared_ptr<DataControllerEntities> DataControllerEntities::instance()
{
	static std::shared_ptr<DataControllerEntities> dataController = std::make_shared <DataControllerEntities>();
	return dataController;
}

int DataControllerEntities::getInventoryWoodforAllWorkers()
{
	int woodCount = 0;
	for (auto& worker : TotalWorkers)
	{
		woodCount += worker->wood;
	}
	return woodCount;
}

void DataControllerEntities::woodConsumeFromAllworkersBuilding(int BuildingCost)
{
	
	for (auto& worker : TotalWorkers)
	{
		if (WoodConsumtionCounter < BuildingCost)
		{
			if (worker->wood <= 1)
			{
				worker->wood -= 1;
				WoodConsumtionCounter++;
			}
		}
		
	}
}
