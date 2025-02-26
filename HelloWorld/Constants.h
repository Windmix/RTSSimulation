#pragma once
#include "memory"
#include "string"
#include "vector"
#include "fstream"
#include "sstream"
class Constants
{
private:
	std::vector<std::vector<char>> data;
public:
	/// <summary>
	/// /////////////////////////
	int ammountOfScouts = 0;////
	int ammountOfBuilders = 0; //
	int ammountOfBuildings = 0;//
	int ammountOfCoalMiners = 0;//
	/// * NO TOUCHING ///////////
	int globalWood = 0;
	int globalCoal = 0;

	static std::shared_ptr<Constants> instance();

	//sim speed
	float simulationSpeed = 100.0f;
	//character stats
	float speed = 1.0f;

	
	//trees
	int totalTrees = 5;
	int maximumAmmountOfBUildings = 1;

	//character ammount
	int maximumScouts = 1;
	int maximumBuilders = 1;
	int maximumCoalMiners = 1;

	//totalworkers > 0 or simulate not simulating properly
	
	int totalWorkers = 50;


	void readFromFile(std::string filepath);
};

