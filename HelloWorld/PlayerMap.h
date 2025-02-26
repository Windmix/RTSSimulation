#pragma once
#include <string>
#include <unordered_set>
#include <vector>
#include <unordered_map>
#include "DataControllerTrees.h"
#include "Constants.h"
#include "Tree.h"



class AstartAlgorithm;

class PlayerMap
{
private:
	int xMaxOffset;
	int yMaxOffset;
	int maxY;
	int maxX;

	int TILESIZE;

	int VectorSizeX;
	int VectorSizeY;

public:

	std::vector<std::vector<char>> map;
	std::unordered_map<int, std::shared_ptr<GameObjectX>> gameObjectsMap;

	std::vector<std::shared_ptr<GameObjectX>> gameObjects; //tiles
	std::vector<Tree> trees;
	

	void drawRectfromGameOBJX(std::shared_ptr<GameObjectX>& thisGameObjectX, bool fill);
	void drawcirclefromTrees(std::shared_ptr<GameObjectX>& thisGameObjectX);
public:

	static std::shared_ptr<PlayerMap> Instance();

	PlayerMap();
	void readMapFromFile(std::string filepath);

	void randomizeMap(); // just for testing

	void SettingUpMap(int OffsetX, int OffsetY, int TILE_SIZE);
	//void settingUpTrees();

	void updateVisibility(std::shared_ptr<GameObjectX>& scout);
	void updateVisibilityStructure(std::shared_ptr<GameObjectX>& tile);


	//void drawPath();
	void drawMap();
	void DrawTrees();
	std::shared_ptr<GameObjectX> getStartObject();
	std::shared_ptr<GameObjectX> getCoalMilObject();
	std::shared_ptr<GameObjectX> getClosestCoalMilObject(std::shared_ptr<GameObjectX>& gameObject);
	std::shared_ptr<GameObjectX> getRandomTileObject();
	std::shared_ptr<GameObjectX> getRandomVisableTileObject(std::shared_ptr<GameObjectX>& GameObject);
	std::shared_ptr<GameObjectX> getGoalObject();


	std::shared_ptr<GameObjectX> getClosestFoggedObject(std::shared_ptr<GameObjectX>& GameObject);

	std::shared_ptr<GameObjectX> getRandomGrassObject(std::shared_ptr<GameObjectX>& GameObject);


	std::shared_ptr<GameObjectX> getRandomFoggedObject(std::shared_ptr<GameObjectX>& GameObject);
	std::shared_ptr<GameObjectX> getClosesFoundTreeObject(std::shared_ptr<GameObjectX>& GameObject);
	std::shared_ptr<GameObjectX> getClosestGrassObject(std::shared_ptr<GameObjectX>& gameObject);

	
	std::vector<std::shared_ptr<GameObjectX>> getNeighbors(std::shared_ptr<GameObjectX>& gameObjectX, bool isScoutUsing);
	std::vector<std::shared_ptr<GameObjectX>> getNeighborsConstant(std::shared_ptr<GameObjectX>& gameObjectX);
	std::vector<std::shared_ptr<GameObjectX>> getNeighborsConstantXXL(std::shared_ptr<GameObjectX>& gameObjectX);


	int getWidth();
	int getHeight();

};

