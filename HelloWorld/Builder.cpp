#include "Builder.h"
#include "BuildingState.h"
#include "constructCoalMilState.h"

Builder::Builder(std::string name)
{
    this->name = name;
    this->speed = 1.0f;
    this->currentState = BuildingState::instance();
    this->frameCounter = 0.0f;
    this->buildingTimer = 0.0f;
}

void Builder::handleMessage(Telegram& msg)
{
    switch (msg.getMessage())
    {
    case MessageType::msg_callBuilding:
    {
        buildingTimer = msg.getDispatchTime() + 60;
        currentState = constructCoalMilState::instance();
        break;
    }
    case MessageType::msg_callNeedBuildingCoal:
    {
        currentState = BuildingState::instance();
    }
    }
}

void Builder::drawPath()
{
}

void Builder::update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    currentState->handle(shared_from_this(), pMap, astarAlgo, deltaTime);
    // Draw debug info (text and circle) on the scout's position

    Play::DrawDebugText((currentStandingGameObject->centrilziedPosition + Play::Point2D(0.0f, -10.0f)), this->name.c_str(), Play::cBlack, true);
    Play::DrawCircle(currentStandingGameObject->centrilziedPosition, 5, Play::cBlue);
}
