#include "WanderingState.h"
#include "PlayerMap.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "DataControllerEntities.h"
#include "DataControllerTrees.h"
#include "GoingToTreeState.h"
#include "UpgradingState.h"
#include "Constants.h"
#include "Scout.h"
#include "Builder.h"

std::shared_ptr<WanderingState> WanderingState::instance()
{
    static std::shared_ptr<WanderingState> wanderingState = std::make_shared<WanderingState>();
    return wanderingState;
}

void WanderingState::handle(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{

    owner->frameCounter += deltaTime;  // Accumulate elapsed time
    std::shared_ptr<Constants> constants = Constants::instance();
    std::shared_ptr<DataControllerEntities> entities = DataControllerEntities::instance();
    std::shared_ptr<DataControllerTrees> trees = DataControllerTrees::instance();

    // Before moving, check if delayTimer is active
    // Define movement speed based on terrain
    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed
    owner->isBusy = false;

    // If no path, find a new wandering path
    if (owner->path.empty())
    {
        auto randomDestination = pMap->getRandomTileObject();
        owner->path = astarAlgo->findPath(owner->currentStandingGameObject, randomDestination, pMap, false);

        // Ensure only one scout request is sent




        for (auto& entityPair : Entity_Manager->getAllEntities())
        {
            // Convert entity to a Worker type (assuming all are stored as base class pointers)
            std::shared_ptr<Worker> worker = std::dynamic_pointer_cast<Worker>(entityPair.second);
            // Ensure entity is a Worker (prevents unnecessary checks)
            if (typeid(*entityPair.second) != typeid(Worker))
            {
                continue;
            }

            

            // If this worker is already upgrading, check the next one
            if (worker->isUpgradingScout || worker->isUpgradingBuilder || worker->isUpgradingCoalMiner)
            {
                continue;
            }

            // Request a Scout if none exists and this worker is available
            if (constants->ammountOfScouts < constants->maximumScouts && !worker->isUpgradingBuilder && !worker->isUpgradingCoalMiner)
            {

                MessageDispatcher::instance()->DispatchMsg(0, worker->getEntityID(), worker->getEntityID(), MessageType::msg_callWeNeedAScout, nullptr);
                worker->isUpgradingScout = true;
           
                constants->ammountOfScouts++;
               
            }
            // Request a Builder if none exists and this worker is available
            if ( constants->ammountOfBuilders < constants->maximumBuilders && !worker->isUpgradingScout && !worker->isUpgradingCoalMiner)
            {

                
                MessageDispatcher::instance()->DispatchMsg(0, worker->getEntityID(), worker->getEntityID(), MessageType::msg_callWeNeedABuilder, nullptr);
                worker->isUpgradingBuilder = true;
                constants->ammountOfBuilders++;
              
                
               
            }
            if (constants->ammountOfCoalMiners < constants->maximumCoalMiners && !worker->isUpgradingScout && !worker->isUpgradingBuilder)
            {


                MessageDispatcher::instance()->DispatchMsg(0, worker->getEntityID(), worker->getEntityID(), MessageType::msg_callWeNeedACoalMiner, nullptr);
                worker->isUpgradingCoalMiner = true;
                constants->ammountOfCoalMiners++;



            }

        }

        // If at least 1 scout exists, assign worker to tree cutting
        if (entities->totalScouts.size() >= 1)
        {
            auto closestTree = pMap->getClosesFoundTreeObject(owner->currentStandingGameObject);
            if (closestTree)
            {
                owner->currentState = GoingToTreeState::instance();
            }
            else
            {
                owner->currentState = WanderingState::instance();
            }
        }
           
   


    }
    // If enough time has passed for movement
    if (owner->frameCounter >= requiredTime)
    {
        owner->frameCounter = 0.0f; // Reset frame counter

      

        // Move step by step instead of teleporting
        if (!owner->path.empty())
        {
            auto nextStep = owner->path.front();
            owner->path.erase(owner->path.begin());

            // Update Worker position
            owner->currentStandingGameObject = nextStep;
        }
    }
}


void WanderingState::enterState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void WanderingState::exitState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool WanderingState::onMessage(std::shared_ptr<Worker> SPWorker, Telegram& telegram)
{
    std::shared_ptr<DataControllerEntities> entities = DataControllerEntities::instance();

    switch (telegram.getMessage())
    {
    case MessageType::msg_callWeNeedAScout:
        if (!SPWorker->isUpgradingScout)  // Only update if not already upgrading
        {
            SPWorker->isUpgradingScout = true;
            return true;  // Message handled successfully
        }
        break;

    case MessageType::msg_callWeNeedABuilder:
        if (!SPWorker->isUpgradingBuilder)  // Only update if not already upgrading
        {
            SPWorker->isUpgradingBuilder = true;
            return true;  // Message handled successfully
        }
        break;

    default:
        break;
    }
    return false; // If message was not handled
}