#pragma once
#include "Telegram.h"
#include "PlayerMap.h"
#include "AstarAlgorithm.h"
#include <memory>

class BaseGameEntity
{
private:
	unsigned int entityID;
	static unsigned int nextValidID;
	void setID(int value);


public:


	virtual void handleMessage(Telegram& msg) = 0;

	// Update function to handle movement and fog of war
	virtual void update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) = 0;

	// Move the Scout to a new tile
	virtual void drawPath() = 0;


	void setEntityID(unsigned int ID);
	unsigned int getEntityID();

	static unsigned int getNextValidID();
};