#include "GameObjectX.h"



GameObjectX::GameObjectX()
{
	this->position = Play::Point2D();
	this->scale = Play::Point2D();
	this->color = Play::cBlack;
	this->isWalkable = false;
	this->isVisable = false;
	this->constructionType = GameObjectType::Grass;
	this->ID = 0;

}

GameObjectX::~GameObjectX()
{
}

GameObjectX::GameObjectX(Play::Point2D pos)
{
	this->position = pos;
}

GameObjectX::GameObjectX(Play::Point2D pos, Play::Point2D centeredPos, Play::Point2D scl, Play::Colour clr, bool isWalkable, bool isVisable, GameObjectType objectType, int id, int weight)
{
	this->position = pos;
	this->centrilziedPosition = centeredPos;
	this->scale = scl;
	this->color = clr;
	this->isWalkable = isWalkable;
	this->constructionType = objectType;
	this->ID = id;
	this->weight = weight;
	this->isVisable = isVisable;
}

GameObjectX::GameObjectX(Play::Point2D pos, Play::Point2D centeredPos, Play::Point2D scl, Play::Colour clr, Play::Colour fogClr, bool isWalkable, bool isVisable, GameObjectType objectType, Tree tree, int id, int weight)
{
	this->position = pos;
	this->centrilziedPosition = centeredPos;
	this->scale = scl;
	this->color = clr;
	this->colorFog = fogClr;
	this->isWalkable = isWalkable;
	this->constructionType = objectType;
	this->ID = id;
	this->weight = weight;
	this->isVisable = isVisable;
	this->tree = tree;
}


void GameObjectX::SetPosition(Play::Point2D& pos)
{
	this->position = pos;
}

void GameObjectX::SetScale(Play::Point2D& scl)
{
	this->scale = scl;
}

void GameObjectX::SetColor(Play::Colour& clr)
{
	this->color = clr;
}

int GameObjectX::CalculateHCost(Play::Point2D& goal)
{
	return std::abs(position.x - goal.x) + std::abs(position.y - goal.y) * 10;
}

int GameObjectX::getFcost()
{
	return gCost + hCost;
}


