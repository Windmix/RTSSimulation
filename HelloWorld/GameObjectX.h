#pragma once
#include <Play.h>
#include <memory>
#include <string>
#include "GameObjectType.h"
#include "Tree.h"


class GameObjectX // is a tile
{

public:
	int ID;

	Play::Point2D position;
	Play::Point2D centrilziedPosition;
	Play::Point2D scale;

	int gCost = 0;  // Cost from start to current node
	int hCost = 0;  // Heuristic cost from current node to end
	int Fcost = 0;

	int weight = 0;

	Play::Colour color;
	Play::Colour colorFog;
	std::shared_ptr<GameObjectX> parent;


	GameObjectType constructionType;

	Tree tree;
	bool isWalkable;
	bool isVisable;

	//coalMil
	int totalWood;
	int TotalCoal;


	

	GameObjectX();
	virtual ~GameObjectX();

	GameObjectX(Play::Point2D pos);
	GameObjectX(Play::Point2D pos, Play::Point2D centeredPos, Play::Point2D scl, Play::Colour clr, bool isWalkable, bool isVisable, GameObjectType objectType, int id, int weight);
	GameObjectX(Play::Point2D pos, Play::Point2D centeredPos, Play::Point2D scl, Play::Colour clr, Play::Colour fogClr, bool isWalkable, bool isVisable, GameObjectType objectType, Tree tree, int id, int weight);
	

	void SetPosition(Play::Point2D& pos);
	void SetScale(Play::Point2D& scl);
	void SetColor(Play::Colour& clr);

	int CalculateHCost(Play::Point2D& goal);
	int getFcost(); // totalCost


};