#include "CuttingWoodState.h"
#include "MessageDispatcher.h"
#include "Clock.h"

std::shared_ptr<CuttingWoodState> CuttingWoodState::instance()
{
    static std::shared_ptr<CuttingWoodState> instance = std::make_shared<CuttingWoodState>();
    return instance;
}

void CuttingWoodState::handle(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    owner->isBusy = true;

    std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();
    std::shared_ptr<Clock> theClock = Clock::instance();



    if (theClock->time >= owner->cuttingCompleteTime)
    {

        owner->frameCounter = 0.0f; // Reset frame counter


       

        if (owner->currentStandingGameObject->constructionType == GameObjectType::Trees)
        {


            // ** IF TREE IS FULLY CUT, REMOVE IT AND FIND A NEW TREE **
            if (owner->currentStandingGameObject->tree.isTreeFullyCutted())  // Tree is fully cut
            {
                owner->currentStandingGameObject->constructionType = GameObjectType::Grass;
                owner->currentStandingGameObject->color = Play::Colour(50.0f, 100.0f, 50.0f);

                // Remove the cut tree from the found trees list
                auto it = std::find(dataControllerTrees->foundTrees.begin(), dataControllerTrees->foundTrees.end(), owner->currentStandingGameObject);
                if (it != dataControllerTrees->foundTrees.end())
                {
                    dataControllerTrees->foundTrees.erase(it);  // Remove cut tree from the list
                }
                MessageDispatcher::instance()->DispatchMsg(0, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callGoingToTree, nullptr);

            }
            if (owner->isWoodFull())  // If the worker has enough wood, go to deposit
            {
                MessageDispatcher::instance()->DispatchMsg(0, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callImFullOfWood, nullptr);
            }

            else
            {
                owner->currentStandingGameObject->tree.TreeIsCut();
                owner->wood += 1;
                MessageDispatcher::instance()->DispatchMsg(1, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callCuttingTree, nullptr);

            }

        }
        if (owner->currentStandingGameObject->constructionType == GameObjectType::Grass)
        {
            MessageDispatcher::instance()->DispatchMsg(0, owner->getEntityID(), owner->getEntityID(), MessageType::msg_callGoingToTree, nullptr);
        }

        
    }
}

void CuttingWoodState::enterState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void CuttingWoodState::exitState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool CuttingWoodState::onMessage(std::shared_ptr<Worker> SPWorker, Telegram& telegram)
{
    return false;
}
