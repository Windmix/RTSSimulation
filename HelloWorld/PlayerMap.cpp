#include "PlayerMap.h"
#include "DataControllerEntities.h"






void PlayerMap::drawRectfromGameOBJX(std::shared_ptr<GameObjectX>& thisGameObjectX, bool fill)
{
    if (thisGameObjectX->isVisable)
    {
        Play::DrawRect(thisGameObjectX->position, thisGameObjectX->scale, thisGameObjectX->color, fill);
    }
    
    else
    {
        Play::DrawRect(thisGameObjectX->position, thisGameObjectX->scale, thisGameObjectX->colorFog, fill);
    }
}

void PlayerMap::drawcirclefromTrees(std::shared_ptr<GameObjectX>& thisGameObjectX)
{
    if (thisGameObjectX->isVisable)
    {
        Play::DrawCircle(thisGameObjectX->centrilziedPosition, 7, Play::Colour(25.0f, 50.0f, 25.0f));
        Play::DrawDebugText(thisGameObjectX->centrilziedPosition, std::to_string(thisGameObjectX->tree.ammountOfTrees).c_str(), Play::Colour(25.0f, 50.0f, 25.0f), true);
    }
}


std::shared_ptr<PlayerMap> PlayerMap::Instance()
{
    std::shared_ptr<PlayerMap> pMap = std::make_shared<PlayerMap>();
    return pMap;
}

PlayerMap::PlayerMap()
{
    VectorSizeY = 0;
}

void PlayerMap::readMapFromFile(std::string filepath)
{

	std::ifstream file(filepath);
	if (!file)
    {
		std::cerr << "Error: Cannot open file!" << std::endl;
		return;
	}

	std::string line = "";
    while (std::getline(file, line))
    {
        map.push_back(std::vector<char>(line.begin(), line.end()));
    }
    file.close();

}

void PlayerMap::randomizeMap()
{
    for (size_t i = 0; i < map.size(); i++)
    {
        for (size_t j = 0; j < map[i].size(); j++)
        {
            // Skip unmovable objects like 'V' (water) or 'B' (rock) to preserve obstacles
            if (map[i][j] == 'V' || map[i][j] == 'B')
                continue;

            // Randomly swap with a nearby tile
            int randI =(rand() % 2 - 1); // -1, 0, or 1
            int randJ = (rand() % 2 - 1);

            if (randI < map.size() && randJ < map[i].size())
                std::swap(map[i][j], map[randI][randJ]);
        }
    }
}


void PlayerMap::SettingUpMap(int OffsetX = 40, int OffsetY = 200, int TILE_SIZE = 20)
{
    TILESIZE = TILE_SIZE;
    int ID = 0;
    maxY = OffsetY + (map.size() * TILE_SIZE);  // Total height of the map
    maxX = OffsetX + (map[0].size() * TILE_SIZE);  // Total width of the map

    VectorSizeX = map[0].size();
  
    this->xMaxOffset = maxX * 2;
    this->yMaxOffset = maxY * 2;
    
    for (int i = 0; i < map.size(); i++)
    {

        for (int j = 0; j < map[i].size(); j++)
        {
            // Inverted Y position
            Play::Point2D position(OffsetX + j * TILE_SIZE, maxY - i * TILE_SIZE);
            Play::Point2D size(OffsetX + j * TILE_SIZE + TILE_SIZE, maxY - i * TILE_SIZE + TILE_SIZE);

            Play::Point2D delta = size - position;
            Play::Point2D centralizedPos = position + (delta / 2);

            bool isWalkable = true;
            bool isVisable = true;
            int weight = 0;
            GameObjectType objectType = GameObjectType::Rock;
            std::string spriteName;
            std::shared_ptr<Constants> constant = Constants::instance();
            Tree tree;

            auto color = Play::cWhite;
            auto colorFog = Play::cWhite;

            if (map[i][j] == 'B')
            {
                //Rock
                objectType = GameObjectType::Rock;
                color = Play::cGrey;
                colorFog = Play::Colour(10.0f, 10.0f, 10.0f);
                isWalkable = false;
                isVisable = false;
                weight = 2;

            }
            else if (map[i][j] == 'M')
            {
                //floor
                objectType = GameObjectType::Grass;
                
                color = Play::Colour(50.0f, 100.0f, 50.0f);
                colorFog = Play::Colour(10.0f, 10.0f, 10.0f);
                isWalkable = true;
                isVisable = false;
                weight = 1;
                
            }
            else if (map[i][j] == 'S')
            {
                objectType = GameObjectType::Start;
                color = Play::cRed;
                
                isWalkable = true;
                isVisable = true;
                weight = 1;
            }
            else if (map[i][j] == 'E')
            {
                objectType = GameObjectType::End;
                color = Play::cOrange;
                isWalkable = true;
                isVisable = false;
                weight = 1;
            }

            else if (map[i][j] == 'G')
            {
                //Start
                objectType = GameObjectType::Swamp;
                color = Play::Colour(65.0f, 33.0f, 10.0f);
                colorFog = Play::Colour(10.0f, 10.0f, 10.0f);
                isWalkable = true;
                isVisable = false;
                weight = 2;
            }
            else if (map[i][j] == 'V')
            {
                //Goal
                objectType = GameObjectType::Water;
                color = Play::Colour(25.0f, 25.0f, 100.0f);
                colorFog = Play::Colour(10.0f, 10.0f, 10.0f);
                isWalkable = false;
                isVisable = false;
                weight = 2;
            }
            else if (map[i][j] == 'T')
            {
                objectType = GameObjectType::Trees;
                color = Play::Colour(20.0f, 100.0f, 0.0f);
                colorFog = Play::Colour(10.0f, 10.0f, 10.0f);
                tree.ammountOfTrees = constant->totalTrees;
                isWalkable = true;
                isVisable = false;
                weight = 1;
            }

            std::shared_ptr<GameObjectX> gameobject =std::make_shared<GameObjectX>(position, centralizedPos, size, color, colorFog, isWalkable, isVisable, objectType,tree, ID, weight);
            gameObjects.push_back(gameobject); // store in vector

        

            gameObjectsMap[ID] = gameobject; // store in map

            ID += 1;
            
        }
        VectorSizeY += 1;

    }
}

//void PlayerMap::settingUpTrees()
//{
//    for (auto& object : gameObjects)
//    {
//       if (object->constructionType == GameObjectType::Trees)
//        {
//           trees.push_back(object);
//        }
//    }
//
//}



void PlayerMap::updateVisibility(std::shared_ptr<GameObjectX>& scout)
{
    std::shared_ptr<DataControllerTrees> trees = DataControllerTrees::instance();
  
    scout->isVisable = true; // The tile the scout is standing on is always visible

    for (auto& object : gameObjects)
    {
        for (auto& neighbor : getNeighborsConstant(scout))
        {

            neighbor->isVisable = true; // Reveal all adjacent 8 tiles

            if (neighbor->constructionType == GameObjectType::Trees)
            {
                if (std::find(trees->foundTrees.begin(), trees->foundTrees.end(), neighbor) == trees->foundTrees.end())
                {
                    trees->foundTrees.push_back(neighbor);
                }
            }
            


        }
    }
}

void PlayerMap::updateVisibilityStructure(std::shared_ptr<GameObjectX>& tile)
{
    for (auto& object :gameObjects)
    {
        for (auto& neighbor : getNeighborsConstantXXL(tile))
        {
            neighbor->isVisable = true; // Reveal all adjacent 8 tiles




        }
    }
}


//void PlayerMap::drawPath()
//{ 
//   
//
//
//}

void PlayerMap::drawMap()
{
    // Step 1: Draw all objects (except scouts)
    for (auto& object : gameObjects)
    {
        drawRectfromGameOBJX(object, true);
       
    }


}

void PlayerMap::DrawTrees()
{
    std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();
    for (auto& object : dataControllerTrees->foundTrees)
    {
        if (object->tree.ammountOfTrees <= 0)
        {

        }
        else 
        {
            drawcirclefromTrees(object);
        }
     
    }
}

std::shared_ptr<GameObjectX> PlayerMap::getStartObject()
{
    for (auto& object : gameObjects)
    {
        if (object->constructionType == GameObjectType::Start)
        {
            updateVisibilityStructure(object);
            return object;
        }

    }
}
std::shared_ptr<GameObjectX> PlayerMap::getCoalMilObject()
{
    for (auto& object : gameObjects)
    {
        if (object->constructionType == GameObjectType::CoalMil)
        {
            updateVisibilityStructure(object);
            return object;
        }

    }
    return nullptr;
}
std::shared_ptr<GameObjectX> PlayerMap::getClosestCoalMilObject(std::shared_ptr<GameObjectX>& gameObject)
{
    std::shared_ptr<GameObjectX> closestcoal = nullptr;

    float minDistance = std::numeric_limits<float>::max();
    auto start = gameObject; // Assuming this is the scout�s position

    for (auto& object : gameObjects)
    {
        if (object->isVisable && object->isWalkable && object->constructionType == GameObjectType::CoalMil) // Ensure it's walkable
        {
            float distance = (object->centrilziedPosition - start->centrilziedPosition).Length();

            if (distance < minDistance)
            {
                minDistance = distance;
                closestcoal = object;
            }
        }
    }
    return closestcoal;
}


std::shared_ptr<GameObjectX> PlayerMap::getRandomTileObject()
{

    // Collect all walkable objects
    int randomIndex = rand() %gameObjects.size();
    auto it =gameObjects.begin();
    std::advance(it, randomIndex);
   return *it;
}
std::shared_ptr<GameObjectX> PlayerMap::getRandomVisableTileObject(std::shared_ptr<GameObjectX>& GameObject)
{

    std::vector<std::shared_ptr<GameObjectX>> Tiles; // Store all valid fogged tiles


    auto start = GameObject; // Assuming this is the scout’s position

    // Collect all walkable & fogged tiles
    for (const auto& object : gameObjects)
    {
        if (object->isVisable && object->isWalkable)
        {
            Tiles.push_back(object);
        }
    }

    // If we found any valid fogged tiles, pick one randomly
    if (!Tiles.empty())
    {
        int randomIndex = rand() % Tiles.size(); // Pick a random index
        if (Tiles[randomIndex]->isVisable)
        {
            return Tiles[randomIndex];
        }
        
    }

    return nullptr; // No fogged tiles found
}





std::shared_ptr<GameObjectX> PlayerMap::getGoalObject()
{
    for (auto& object : gameObjects)
    {
        if (object->constructionType == GameObjectType::End)
        {
            return object;
        }

    }
}



std::shared_ptr<GameObjectX> PlayerMap::getClosestFoggedObject(std::shared_ptr<GameObjectX>& GameObject)
{
    std::shared_ptr<GameObjectX> closestFogged = nullptr;

    float minDistance = std::numeric_limits<float>::max();
    auto start = GameObject; // Assuming this is the scout�s position

    for (auto& object : gameObjects)
    {
        if (!object->isVisable && object->isWalkable) // Ensure it's walkable
        {
            float distance = (object->centrilziedPosition - start->centrilziedPosition).Length();

            if (distance < minDistance)
            {
                minDistance = distance;
                closestFogged = object;
            }
        }
    }
    return closestFogged;
}

std::shared_ptr<GameObjectX> PlayerMap::getRandomGrassObject(std::shared_ptr<GameObjectX>& GameObject)
{


    std::vector<std::shared_ptr<GameObjectX>> grassTiles; // Store all valid fogged tiles


    auto start = GameObject; // Assuming this is the scout’s position

    // Collect all walkable & fogged tiles
    for (const auto& object : gameObjects)
    {
        if (object->isVisable && object->constructionType == GameObjectType::Grass)
        {
            grassTiles.push_back(object);
        }
    }

    // If we found any valid fogged tiles, pick one randomly
    if (!grassTiles.empty())
    {

        int randomIndex = rand() % grassTiles.size(); // Pick a random index
        if (grassTiles[randomIndex]->isVisable)
        {
            return grassTiles[randomIndex];
        }
    }

    return nullptr; // No fogged tiles found
}


std::shared_ptr<GameObjectX> PlayerMap::getRandomFoggedObject(std::shared_ptr<GameObjectX>& GameObject)
{


    std::vector<std::shared_ptr<GameObjectX>> foggedTiles; // Store all valid fogged tiles
   

    auto start = GameObject; // Assuming this is the scout’s position

    // Collect all walkable & fogged tiles
    for (const auto& object : gameObjects)
    {
        if (!object->isVisable && object->isWalkable)
        {
            foggedTiles.push_back(object);
        }
    }

    // If we found any valid fogged tiles, pick one randomly
    if (!foggedTiles.empty())
    {
        int randomIndex = rand() % foggedTiles.size(); // Pick a random index
        return foggedTiles[randomIndex];
    }

    return nullptr; // No fogged tiles found
}

std::shared_ptr<GameObjectX> PlayerMap::getClosesFoundTreeObject(std::shared_ptr<GameObjectX>& GameObject)
{
    std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();

    if (dataControllerTrees->foundTrees.empty())
    {
        return nullptr;  // No trees found
    }

    std::shared_ptr<GameObjectX> closestTree = nullptr;
    float minDistance = std::numeric_limits<float>::max();

    auto start = GameObject; // Assuming this is the scout’s position

    for (const auto& object : dataControllerTrees->foundTrees)
    {
        float distance = (object->centrilziedPosition - start->centrilziedPosition).Length(); // Faster

        if (distance < minDistance)
        {
            minDistance = distance;
            closestTree = object;
        }
    }

    return closestTree; // Returns the closest found tree or nullptr if none exist
}

std::shared_ptr<GameObjectX> PlayerMap::getClosestGrassObject(std::shared_ptr<GameObjectX>& gameObject)
{

    std::shared_ptr<GameObjectX> closestGrass = nullptr;

    float minDistance = std::numeric_limits<float>::max();
    auto start = gameObject; // Assuming this is the scout�s position

    for (auto& object : gameObjects)
    {
        if (object->isVisable && object->isWalkable) // Ensure it's walkable
        {
            float distance = (object->centrilziedPosition - start->centrilziedPosition).Length();

            if (distance < minDistance)
            {
                minDistance = distance;
                closestGrass = object;
            }
        }
    }
    return closestGrass;
}

//
//bool PlayerMap::isPathContaining(std::shared_ptr<GameObjectX> gameobject)
//{
//    return std::find(this->path.begin(), path.end(), gameobject) != path.end();
//}

std::vector<std::shared_ptr<GameObjectX>> PlayerMap::getNeighbors(std::shared_ptr<GameObjectX>& gameObjectX,bool isScoutUsing)
{
    std::vector<std::shared_ptr<GameObjectX>> neighbours;

    int currentID = gameObjectX->ID;

    std::vector<int> neighborIDs =
    {
        currentID - 1,    // Left
        currentID + 1,    // Right
        currentID + VectorSizeX,    // Up
        currentID - VectorSizeX,    // Down
        currentID + VectorSizeX - 1, // Up-left
        currentID + VectorSizeX + 1, // Up-right
        currentID - VectorSizeX - 1, // Down-left
        currentID - VectorSizeX + 1,  // Down-right
    };

    for (int neighborID : neighborIDs)
    {
        // Check if the neighbor ID exists in the gameObjects map
        auto neighbor = gameObjectsMap.find(neighborID);

        if (neighbor != gameObjectsMap.end())
        {
            bool isDiagonal = 
               (neighborID == currentID + VectorSizeX - 1 || // Up-left
                neighborID == currentID + VectorSizeX + 1 || // Up-right
                neighborID == currentID - VectorSizeX - 1 || // Down-left
                neighborID == currentID - VectorSizeX + 1);  // Down-right

            if (isDiagonal)
            {
                // For diagonal moves, check if the adjacent horizontal and vertical tiles are walkable
                int dx;
                int dy;

                int neighborRow = neighborID / VectorSizeX;
                int neighborCol = neighborID % VectorSizeX;
                int currentRow = currentID / VectorSizeX;
                int currentCol = currentID % VectorSizeX;

                if (VectorSizeX == VectorSizeY)
                {
                    

                    dx = neighborCol - currentCol;  // Horizontal difference (left-right)
                    dy = neighborRow - currentRow;  // Vertical difference (up-down)

                }
                if (VectorSizeX != VectorSizeY)
                {
                    dx = neighborCol - currentCol;  // Horizontal difference (left-right)
                    dy = neighborRow - currentRow;  // Vertical difference (up-down)
                }
                int horizontalID = currentID + dx; // Horizontal neighbor
                int verticalID = currentID + dy * VectorSizeX; // Vertical neighbor

                auto horizontalNeighbor = gameObjectsMap.find(horizontalID);
                auto verticalNeighbor = gameObjectsMap.find(verticalID);

                if (isScoutUsing)
                {
                    // Only allow diagonal movement if both adjacent tiles are walkable
                    if (horizontalNeighbor != gameObjectsMap.end() && horizontalNeighbor->second->constructionType != GameObjectType::Rock && verticalNeighbor != gameObjectsMap.end() && verticalNeighbor->second->constructionType != GameObjectType::Rock
                        && horizontalNeighbor != gameObjectsMap.end() && horizontalNeighbor->second->constructionType != GameObjectType::Water && verticalNeighbor != gameObjectsMap.end() && verticalNeighbor->second->constructionType != GameObjectType::Water)
                    {
                        neighbours.push_back(neighbor->second);

                    }
                    
                }
                else
                {
                    // Only allow diagonal movement if both adjacent tiles are walkable
                    if (horizontalNeighbor != gameObjectsMap.end() && horizontalNeighbor->second->constructionType != GameObjectType::Rock && verticalNeighbor != gameObjectsMap.end() && verticalNeighbor->second->constructionType != GameObjectType::Rock
                        && horizontalNeighbor != gameObjectsMap.end() && horizontalNeighbor->second->constructionType != GameObjectType::Water && verticalNeighbor != gameObjectsMap.end() && verticalNeighbor->second->constructionType != GameObjectType::Water && neighbor->second->isVisable)
                    {
                        neighbours.push_back(neighbor->second);

                    }
                   
                }
            }
            else
            {
                if (isScoutUsing)
                {
                    // For non-diagonal moves, just add the neighbor if it's not a Rock
                    if (neighbor->second->constructionType != GameObjectType::Rock && neighbor->second->constructionType != GameObjectType::Water)
                    {
                        neighbours.push_back(neighbor->second);
                    }
               
                }
                else 
                {
                    // For non-diagonal moves, just add the neighbor if it's not a Rock
                    if (neighbor->second->constructionType != GameObjectType::Rock && neighbor->second->constructionType != GameObjectType::Water && neighbor->second->isVisable)
                    {
                        neighbours.push_back(neighbor->second);
                    }
                }
                
            }
        }
    }
    return neighbours;
}

std::vector<std::shared_ptr<GameObjectX>> PlayerMap::getNeighborsConstant(std::shared_ptr<GameObjectX>& gameObjectX)
{
    std::vector<std::shared_ptr<GameObjectX>> neighbours;

    int currentID = gameObjectX->ID;

    std::vector<int> neighborIDs =
    {
        currentID - 1,    // Left
        currentID + 1,    // Right
        currentID + VectorSizeX,    // Up
        currentID - VectorSizeX,    // Down
        currentID + VectorSizeX - 1, // Up-left
        currentID + VectorSizeX + 1, // Up-right
        currentID - VectorSizeX - 1, // Down-left
        currentID - VectorSizeX + 1,  // Down-right
    };
    for (int neighborID : neighborIDs)
    {
        // Check if the neighbor ID exists in the gameObjects map
        auto neighbor = gameObjectsMap.find(neighborID);
        neighbours.push_back(neighbor->second);
    }
    return neighbours;
}

std::vector<std::shared_ptr<GameObjectX>> PlayerMap::getNeighborsConstantXXL(std::shared_ptr<GameObjectX>& gameObjectX)
{
    std::vector<std::shared_ptr<GameObjectX>> neighbours;

    int currentID = gameObjectX->ID;

    std::vector<int> neighborIDs = {
        // Row -2 (Topmost row)
        currentID - (2 * VectorSizeX) - 2, currentID - (2 * VectorSizeX) - 1, currentID - (2 * VectorSizeX), currentID - (2 * VectorSizeX) + 1, currentID - (2 * VectorSizeX) + 2,

        // Row -1
        currentID - VectorSizeX - 2, currentID - VectorSizeX - 1, currentID - VectorSizeX, currentID - VectorSizeX + 1, currentID - VectorSizeX + 2,

        // Row 0 (Including center)
        currentID - 2, currentID - 1, currentID, currentID + 1, currentID + 2,

        // Row +1
        currentID + VectorSizeX - 2, currentID + VectorSizeX - 1, currentID + VectorSizeX, currentID + VectorSizeX + 1, currentID + VectorSizeX + 2,

        // Row +2 (Bottommost row)
        currentID + (2 * VectorSizeX) - 2, currentID + (2 * VectorSizeX) - 1, currentID + (2 * VectorSizeX), currentID + (2 * VectorSizeX) + 1, currentID + (2 * VectorSizeX) + 2
    };


    for (int neighborID : neighborIDs)
    {
        // Check if the neighbor ID exists in the gameObjects map
        auto neighbor = gameObjectsMap.find(neighborID);
        neighbours.push_back(neighbor->second);
    }
    return neighbours;
}



int PlayerMap::getWidth()
{
    return this->VectorSizeX;
}

int PlayerMap::getHeight()
{
    return this->VectorSizeY;
}

