#include "Constants.h"
#include "cassert"

std::shared_ptr<Constants> Constants::instance()
{
	static std::shared_ptr<Constants> instance = std::make_shared<Constants>();
	return instance;
}

void Constants::readFromFile(std::string filepath)
{
	std::ifstream file(filepath);
	if (!file)
	{
		assert(false && "can not open file");
	}

	std::string line = "";
	while (std::getline(file, line))
	{
		std::stringstream ss(line);
		std::string key;
		std::string value;

		if (std::getline(ss, key, '=') && std::getline(ss, value))
		{
			key = key.substr(key.find_first_not_of(" "), key.find_last_not_of(" ") + 1);
			value = value.substr(value.find_first_not_of(" "), value.find_last_not_of(" ") + 1);

			// Set the corresponding variables based on the key
			if (key == "totalTrees") {
				totalTrees = std::stoi(value);
			}
			else if (key == "maximumAmmountOfBuildings") 
			{
				maximumAmmountOfBUildings = std::stoi(value);
			}
			else if (key == "maximumScouts") 
			{
				maximumScouts = std::stoi(value);
			}
			else if (key == "maximumBuilders")
			{
				maximumBuilders = std::stoi(value);
			}
			else if (key == "maximumCoalMiners")
			{
				maximumCoalMiners = std::stoi(value);
			}
			else if (key == "totalWorkers")
			{
				totalWorkers = std::stoi(value);
			}
			else if (key == "simulationSpeed") 
			{
				simulationSpeed = std::stof(value);
			}
			else if (key == "speed")
			{
				speed = std::stoi(value);
			}
		}
	}
	file.close();
}


