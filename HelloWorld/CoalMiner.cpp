#include "CoalMiner.h"
#include "MakingCoalState.h"


CoalMiner::CoalMiner(std::string name)
{
    this->name = name;
    this->speed = 1.0f;
    this->currentState = MakingCoalState::instance();
    this->frameCounter = 0.0f;
    this->innerTimer = 0.0f;
}

void CoalMiner::handleMessage(Telegram& msg)
{

}

void CoalMiner::drawPath()
{
}

void CoalMiner::update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    currentState->handle(shared_from_this(), pMap, astarAlgo, deltaTime);
    // Draw debug info (text and circle) on the scout's position

    Play::DrawDebugText((currentStandingGameObject->centrilziedPosition + Play::Point2D(0.0f, -10.0f)), this->name.c_str(), Play::cBlack, true);
    Play::DrawCircle(currentStandingGameObject->centrilziedPosition, 5, Play::cWhite);
}

