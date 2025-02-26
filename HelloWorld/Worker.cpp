
#include "GoingToTreeState.h"
#include "WanderingState.h"
#include "EntityManager.h"
#include "CuttingWoodState.h"
#include "UpgradingState.h"
#include "DepositState.h"
#include "Clock.h"
#include "Telegram.h"

Worker::Worker(std::string name, float speed)
{
    this->name = name;
    this->speed = speed;
    this->currentState = WanderingState::instance();
    this->frameCounter = 0;


    coal = 0;
    iron = 0;
    wood = 0;

    this->upgradeCompleteTime = 0;
    this->cuttingCompleteTime = 0;
    this->ammoutIsConverting = 0;
    this->isUpgradingBuilder = false;
    this->isUpgradingCoalMiner = false;
    this->isUpgradingScout = false;

    this->isBusy = false;
}

void Worker::handleMessage(Telegram& msg)
{
    std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();
    std::shared_ptr<PlayerMap> pMap = PlayerMap::Instance();
    std::shared_ptr<AstartAlgorithm> aStarAlgo = AstartAlgorithm::Instance();
    std::shared_ptr<Constants> constant = Constants::instance();

    switch (msg.getMessage())
    {

    case MessageType::msg_callWeNeedAScout:
    {
        currentState = UpgradingState::instance();
        upgradeCompleteTime = msg.getDispatchTime() + 60;
       
        // Store the upgrade completion time
        break;

    }
    case MessageType::msg_callWeNeedABuilder:
    {
        currentState = UpgradingState::instance();
        upgradeCompleteTime = msg.getDispatchTime() + 120;
        
        // Store the upgrade completion time
        break;
    }
    case MessageType::msg_callWeNeedACoalMiner:
    {
        currentState = UpgradingState::instance();
        upgradeCompleteTime = msg.getDispatchTime() + 120;

        // Store the upgrade completion time
        break;
    }
    case MessageType::msg_callCuttingTree:
    {
        cuttingCompleteTime = msg.getDispatchTime() + 30;
        currentState = CuttingWoodState::instance();
        break;
      
    }
    case MessageType::msg_callGoingToTree:
    {
        currentState = GoingToTreeState::instance();
        break;
    }
    case MessageType::msg_callImFullOfWood:
        currentState = DepositState::instance();
        break;
    }
}


bool Worker::isWoodFull()
{
    if (wood >= 1)
    {
        return true;
    }
    return false;
}

bool Worker::hasUpgradedScout()
{
    // Example: If the worker's state has transitioned to Scout or if other conditions indicate the upgrade has happened
    return dynamic_cast<Scout*>(this) != nullptr;
}

void Worker::drawPath()
{
}

void Worker::update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    currentState->handle(shared_from_this(), pMap, astarAlgo, deltaTime);
    // Draw debug info (text and circle) on the scout's position

    Play::DrawDebugText((currentStandingGameObject->centrilziedPosition + Play::Point2D(0.0f, -10.0f)), this->name.c_str(), Play::cBlack, true);
    Play::DrawCircle(currentStandingGameObject->centrilziedPosition, 5, Play::cOrange);
}
