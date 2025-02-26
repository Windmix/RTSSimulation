#include "AstarAlgorithm.h"
#include "math.h"



bool AstartAlgorithm::containsInOpenList(std::shared_ptr<GameObjectX>& gameobject)
{
    return openSet.find(gameobject) != openSet.end();
}

std::shared_ptr<AstartAlgorithm> AstartAlgorithm::Instance()
{
    std::shared_ptr<AstartAlgorithm> astarAlgorithm = std::make_shared<AstartAlgorithm>();
    return astarAlgorithm;
}

std::vector<std::shared_ptr<GameObjectX>> AstartAlgorithm::findPath(std::shared_ptr<GameObjectX> start, std::shared_ptr<GameObjectX> end, std::shared_ptr<PlayerMap> map, bool isScoutUsing)
{
    openList = {};
    openSet.clear();
    closedList.clear();
  
  


    openList.push(start); 
    openSet.insert(start);
    std::shared_ptr<GameObjectX> currentGameObjectX;

    while (!openList.empty())
    {
        currentGameObjectX = openList.top();
        openList.pop();
        openSet.erase(currentGameObjectX);

        closedList.insert(currentGameObjectX);
   
        if (currentGameObjectX->ID == end->ID)
        {
            return retracePath(start, end);

        }
        for (auto& neighbor : map->getNeighbors(currentGameObjectX, isScoutUsing))
        {
            if (!neighbor->isWalkable || closedList.contains(neighbor))
            {
                continue;
            }

            int NewMovementCostToNeighbour = currentGameObjectX->gCost  + getDistance(currentGameObjectX, neighbor) * currentGameObjectX->weight;

            if (NewMovementCostToNeighbour < neighbor->gCost || !containsInOpenList(neighbor))
            {
                neighbor->gCost = NewMovementCostToNeighbour;
                neighbor->hCost = getDistance(neighbor, end);
                neighbor->parent = currentGameObjectX;

                if (!containsInOpenList(neighbor))
                {
                    openList.push(neighbor);
                    openSet.insert(neighbor);
                }
            }
            // **Only update visualization every 60 iterations**
   
        }
    }

    return retracePath(start,currentGameObjectX);
}

int AstartAlgorithm::getDistance(std::shared_ptr<GameObjectX>& objectA, std::shared_ptr<GameObjectX>& objectB)
{
    int distX = abs(objectA->centrilziedPosition.x - objectB->centrilziedPosition.x);
    int distY = abs(objectA->centrilziedPosition.y - objectB->centrilziedPosition.y);
    if (distX > distY)
    {
        return 14 * distY + 10 * (distX - distY);
    }
    return 14 * distX + 10 * (distY - distX);
}

std::vector<std::shared_ptr<GameObjectX>> AstartAlgorithm::retracePath(std::shared_ptr<GameObjectX>& startObject, std::shared_ptr<GameObjectX>& endObject)
{
    std::vector<std::shared_ptr<GameObjectX>> path;

    std::shared_ptr<GameObjectX> currentObject = endObject;
    while (currentObject != startObject)
    {
        path.push_back(currentObject);
        currentObject = currentObject->parent;
    }
    std::reverse(path.begin(), path.end());

    return path;
}


