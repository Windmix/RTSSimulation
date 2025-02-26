#include "GoingToTreeState.h"
#include "DataControllerTrees.h"
#include "MessageDispatcher.h"
#include "DepositState.h"
#include "WanderingState.h"
#include "PlayerMap.h"

std::shared_ptr<GoingToTreeState> GoingToTreeState::instance()
{
    static std::shared_ptr<GoingToTreeState> workingState = std::make_shared<GoingToTreeState>();
    return workingState;
}
void GoingToTreeState::handle(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, 
                                     std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();
    owner->frameCounter += deltaTime;  // Accumulate the time passed
    owner->isBusy = true;
    // ** FIND A NEW TREE IF PATH IS EMPTY AND FOUND TREES IS NOT EMPTY **
    if (owner->path.empty())  // Ensure there are trees to cut
    {
   
        // Get the closest tree from the found trees list

        auto closestTree = pMap->getClosesFoundTreeObject(owner->currentStandingGameObject);
        if (closestTree)
        {
            owner->path = astarAlgo->findPath(owner->currentStandingGameObject, closestTree, pMap, false);
        }
        else
        {
            owner->currentState = WanderingState::instance();
        }
     
    }

    // ** CUT TREE IF STANDING ON ONE **
    if (owner->currentStandingGameObject->constructionType == GameObjectType::Trees && !owner->isWoodFull())
    {
    
        MessageDispatcher::instance()->DispatchMsg(1, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callCuttingTree, nullptr);
        
    }
    if(owner->isWoodFull())
    {
        MessageDispatcher::instance()->DispatchMsg(0, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callImFullOfWood, nullptr);
    }

    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed

    if (owner->frameCounter >= requiredTime)
    {
        owner->frameCounter = 0.0f;

        // Move towards the next tree step by step
        if (!owner->path.empty())
        {
            auto nextStep = owner->path.front();
            owner->path.erase(owner->path.begin());

            // Update Worker position
            owner->currentStandingGameObject = nextStep;
        }
    }
}
void GoingToTreeState::enterState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{

}

void GoingToTreeState::exitState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{

}

bool GoingToTreeState::onMessage(std::shared_ptr<Worker> SPWorker, Telegram& telegram)
{
    return false;
}
