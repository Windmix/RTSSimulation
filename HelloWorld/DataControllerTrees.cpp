#include "DataControllerTrees.h"

std::shared_ptr<DataControllerTrees>DataControllerTrees::instance()
{
	static std::shared_ptr<DataControllerTrees> dataController = std::make_shared <DataControllerTrees>();
	return dataController;
}
