#include "DepositState.h"
#include "GoingToTreeState.h"
#include "MessageDispatcher.h"
#include "WanderingState.h"

std::shared_ptr<DepositState> DepositState::instance()
{
    static std::shared_ptr<DepositState> depositState = std::make_shared<DepositState>();
    return depositState;
}

void DepositState::handle(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    owner->isBusy = true;


    // If enough time has passed for movement

    if (owner->path.empty())
    {

        auto GotoCoalmil = pMap->getClosestCoalMilObject(owner->currentStandingGameObject);
        if (GotoCoalmil)
        {
            owner->path = astarAlgo->findPath(owner->currentStandingGameObject, GotoCoalmil, pMap, false);
        }
        else
        {
            owner->currentState = WanderingState::instance();
        }
      

        // Check if worker has reached the spawn
        if (owner->currentStandingGameObject->constructionType == GameObjectType::CoalMil)
        {
            if (owner->wood <= 0)
            {
                MessageDispatcher::instance()->DispatchMsg(0, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callGoingToTree, nullptr);
            }
            if (owner->wood > 0)
            {
                owner->currentStandingGameObject->totalWood += 1;
                owner->wood -= 1;

            }
           
        }
    }

    std::shared_ptr<Clock> theClock = Clock::instance();

    // If the upgrade time has passed, convert to a Scout
    owner->frameCounter += deltaTime;  // Accumulate elapsed time
    std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();

    // Define movement speed based on terrain
    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed

    if (owner->frameCounter >= requiredTime)
    {
        owner->frameCounter = 0.0f;

        // Move step by step towards spawn
        if (!owner->path.empty())
        {
            auto nextStep = owner->path.front();
            owner->path.erase(owner->path.begin());

            // Update Worker position
            owner->currentStandingGameObject = nextStep;
        }
        
    }
   
}



void DepositState::enterState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void DepositState::exitState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool DepositState::onMessage(std::shared_ptr<Worker> SPWorker, Telegram& telegram)
{
    return false;
}
