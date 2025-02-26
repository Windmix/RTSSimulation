#include "ScoutingState.h"
#include "PlayerMap.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "DataControllerEntities.h"
#include "DataControllerTrees.h"
#include "Worker.h"





std::shared_ptr<ScoutingState> ScoutingState::instance()
{
    static std::shared_ptr<ScoutingState> scoutingState = std::make_shared<ScoutingState>();
    return scoutingState;
}

void ScoutingState::handle(std::shared_ptr<Scout> owner, std::shared_ptr<PlayerMap>& pMap,
    std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    owner->frameCounter += deltaTime;
    auto dataControllerTrees = DataControllerTrees::instance();
    auto dataControllerEntities = DataControllerEntities::instance();
    
    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed

    if (owner->path.empty())
    {
        auto closestFogged = pMap->getRandomFoggedObject(owner->currentStandingGameObject);
        owner->path = astarAlgo->findPath(owner->currentStandingGameObject, closestFogged, pMap, true);
    }
    if (owner->frameCounter >= requiredTime)
    {
        owner->frameCounter = 0.0f;
        if (!owner->path.empty())
        {


            auto nextStep = owner->path.front();
            owner->path.erase(owner->path.begin());
            owner->currentStandingGameObject = nextStep;
              pMap->updateVisibility(owner->currentStandingGameObject);

        }
    }
  
    

   
}




void ScoutingState::enterState(std::shared_ptr<Scout> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void ScoutingState::exitState(std::shared_ptr<Scout> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool ScoutingState::onMessage(std::shared_ptr<Scout> SPScout, Telegram& telegram)
{
    return false;
}
