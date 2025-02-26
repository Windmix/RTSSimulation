#include "constructCoalMilState.h"
#include "MessageDispatcher.h"
#include "Constants.h"
#include "DataControllerEntities.h"

std::shared_ptr<constructCoalMilState> constructCoalMilState::instance()
{
    static std::shared_ptr<constructCoalMilState> instance = std::make_shared<constructCoalMilState>();
    return instance;
}

void constructCoalMilState::handle(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    int costOfCoalmile = 10;
    std::shared_ptr<Constants> constants = Constants::instance();
    std::shared_ptr<Clock> theClock = Clock::instance();
    std::shared_ptr<DataControllerEntities> entities = DataControllerEntities::instance();

    owner->frameCounter += deltaTime;

    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed
    if (theClock->time >= owner->buildingTimer)
    {
        if (owner->currentStandingGameObject->constructionType == GameObjectType::Grass && constants->maximumAmmountOfBUildings > constants->ammountOfBuildings && entities->getInventoryWoodforAllWorkers() >= 10)
        {
          
            entities->woodConsumeFromAllworkersBuilding(costOfCoalmile);
            owner->currentStandingGameObject->constructionType = GameObjectType::CoalMil;
            owner->currentStandingGameObject->color = Play::cOrange;
            owner->currentStandingGameObject->totalWood = 0;
            owner->currentStandingGameObject->totalWood = 0;
            constants->ammountOfBuildings++;

  
        }

        if (owner->currentStandingGameObject->constructionType != GameObjectType::Grass && constants->maximumAmmountOfBUildings > constants->ammountOfBuildings)
        {
            MessageDispatcher::instance()->DispatchMsg(0, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callNeedBuildingCoal, nullptr);
        }
        else
        {


            //walk
            if (owner->frameCounter >= requiredTime)
            {
                owner->frameCounter = 0.0f;
                if (owner->path.empty())
                {
                    auto randomDestination = pMap->getRandomVisableTileObject(owner->currentStandingGameObject);
                    if (randomDestination)
                    {
                        owner->path = astarAlgo->findPath(owner->currentStandingGameObject, randomDestination, pMap, false);
                    }
                    else
                    {
                       
                    }

                }


                if (!owner->path.empty())
                {


                    auto nextStep = owner->path.front();
                    owner->path.erase(owner->path.begin());
                    owner->currentStandingGameObject = nextStep;

                }
            }
        }
    }
    else
    {

    }
  
   
  


}

void constructCoalMilState::enterState(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void constructCoalMilState::exitState(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool constructCoalMilState::onMessage(std::shared_ptr<Builder> SPWBuilder, Telegram& telegram)
{
    return false;
}
