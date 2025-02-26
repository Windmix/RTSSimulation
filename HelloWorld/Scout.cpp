#include "Scout.h"
#include "WanderingState.h"
#include "ScoutingState.h"
#include "Telegram.h"




Scout::Scout(std::string name)
{
	this->name = name;
    this->speed = 1.0f;
    this->currentState = ScoutingState::instance();
    this->frameCounter = 0;
}

void Scout::handleMessage(Telegram& msg)
{

}

void Scout::drawPath()
{
    static int pathUpdateIndex = 0;
    static Play::Colour previousColor;

    // Only change the color for the first path object and then restore the previous one
    if (pathUpdateIndex < path.size())
    {
        auto& currentObject = path[pathUpdateIndex];

        if (pathUpdateIndex == 0)  // For the first object
        {
            // Store the current color of the first object
            //previousColor = currentObject->color;
            //currentObject->SetColor(Play::cMagenta);  // Set to magenta

           
        }
        else if(pathUpdateIndex > 0) // For subsequent objects
        {
            // Revert the color of the previous object to its stored color
        /*    auto& prevObject = path[pathUpdateIndex - 1];
            prevObject->SetColor(previousColor);*/

            // Store the current object's color
            //previousColor = currentObject->color;
            //currentObject->SetColor(Play::cMagenta);  // Set the current object to magenta
          

            pathUpdateIndex++;  // Move to the next node for the next update
        }
       
       
    }
   
}

void Scout::update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
    currentState->handle(shared_from_this(), pMap, astarAlgo, deltaTime);
    // Draw debug info (text and circle) on the scout's position

    Play::DrawDebugText((currentStandingGameObject->centrilziedPosition + Play::Point2D(0.0f, -10.0f)), this->name.c_str(), Play::cBlack, true);
    Play::DrawCircle(currentStandingGameObject->centrilziedPosition, 5, Play::cBlack);
}
    
 

