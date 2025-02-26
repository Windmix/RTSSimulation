#include "BaseGameEntity.h"
#include "assert.h"

unsigned BaseGameEntity::nextValidID = 0;


void BaseGameEntity::setID(int value)
{
	assert(value >= nextValidID && "ID isn ot valid!");

	entityID = value;
	++nextValidID;
}

void BaseGameEntity::setEntityID(unsigned int ID)
{
	setID(ID);
}


unsigned int BaseGameEntity::getEntityID()
{
	return this->entityID;
}

unsigned int BaseGameEntity::getNextValidID()
{
	return nextValidID;
}
