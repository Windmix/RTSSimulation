#include "BuildingState.h"
#include "MessageDispatcher.h"
#include "DataControllerEntities.h"

std::shared_ptr<BuildingState> BuildingState::instance() // acually searching for tile state xd
{

    static std::shared_ptr<BuildingState> buildingState = std::make_shared<BuildingState>();
    return buildingState;
}

void BuildingState::handle(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    int costOfCoalmile = 10;
    std::shared_ptr<DataControllerEntities> entities = DataControllerEntities::instance();
   
    if (owner->path.empty())
    {

        auto randomGrass = pMap->getRandomGrassObject(owner->currentStandingGameObject);

        if (randomGrass && entities->getInventoryWoodforAllWorkers() >= costOfCoalmile)
        {
            owner->path = astarAlgo->findPath(owner->currentStandingGameObject, randomGrass, pMap, true);
        }
        else
        {
            auto randomDestination = pMap->getRandomVisableTileObject(owner->currentStandingGameObject);
            if (randomDestination)
            {
                owner->path = astarAlgo->findPath(owner->currentStandingGameObject, randomDestination, pMap, false);
            }
        }
       
    }
    if (owner->currentStandingGameObject->constructionType == GameObjectType::Grass && entities->getInventoryWoodforAllWorkers() >= costOfCoalmile)
    {

        MessageDispatcher::instance()->DispatchMsg(1, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callBuilding, nullptr);
        
       

    }

    owner->frameCounter += deltaTime;
    std::shared_ptr<Constants> constants = Constants::instance();
    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed

    //walk
    if (owner->frameCounter >= requiredTime)
    {
        owner->frameCounter = 0.0f;
        if (!owner->path.empty())
        {


            auto nextStep = owner->path.front();
            owner->path.erase(owner->path.begin());
            owner->currentStandingGameObject = nextStep;

        }
    }

   
}

void BuildingState::enterState(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void BuildingState::exitState(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool BuildingState::onMessage(std::shared_ptr<Builder> SPWBuilder, Telegram& telegram)
{
    return false;
}
