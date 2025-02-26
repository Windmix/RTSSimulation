#include "MakingCoalState.h"

std::shared_ptr<MakingCoalState> MakingCoalState::instance()
{
    static std::shared_ptr<MakingCoalState> instance = std::make_shared<MakingCoalState>();
    return instance;
}

void MakingCoalState::handle(std::shared_ptr<CoalMiner> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{

    std::shared_ptr<Constants> constants = Constants::instance();

    owner->frameCounter += deltaTime;
    if (owner->currentStandingGameObject->totalWood >= 2)
    {
        owner->innerTimer += deltaTime * constants->simulationSpeed;
    }

    float baseTime = (owner->currentStandingGameObject->constructionType == GameObjectType::Swamp)
        ? 20.0f  // Swamp (20s per tile)
        : 10.0f; // Grass (10s per tile)
    float requiredTime = baseTime / owner->speed; // Adjust for worker speed

    if (owner->currentStandingGameObject->constructionType == GameObjectType::CoalMil )
    {
        if (owner->currentStandingGameObject->totalWood >= 2 && owner->innerTimer >= 30.0f)
        {
            owner->currentStandingGameObject->totalWood -= 2;
            owner->currentStandingGameObject->TotalCoal += 1;
            owner->innerTimer = 0.0f;
        }
        else
        {
            auto randomDestination = pMap->getRandomVisableTileObject(owner->currentStandingGameObject);
            owner->path = astarAlgo->findPath(owner->currentStandingGameObject, randomDestination, pMap, false);
        }
     
        
      

    }
    else if (owner->frameCounter >= requiredTime)
    {
        if (owner->path.empty())
        {
            auto closeCoalMill = pMap->getClosestCoalMilObject(owner->currentStandingGameObject);
            if (closeCoalMill)
            {
                owner->path = astarAlgo->findPath(owner->currentStandingGameObject, closeCoalMill, pMap, false);
            }
            else
            {
                auto randomDestination = pMap->getRandomVisableTileObject(owner->currentStandingGameObject);
                owner->path = astarAlgo->findPath(owner->currentStandingGameObject, randomDestination, pMap, false);
            }
           
            
        }
        owner->frameCounter = 0.0f;
        if (!owner->path.empty())
        {


            auto nextStep = owner->path.front();
            owner->path.erase(owner->path.begin());
            owner->currentStandingGameObject = nextStep;

        }

    }
   
}

void MakingCoalState::enterState(std::shared_ptr<CoalMiner> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

void MakingCoalState::exitState(std::shared_ptr<CoalMiner> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool MakingCoalState::onMessage(std::shared_ptr<CoalMiner> SPCoalMiner, Telegram& telegram)
{
    return false;
}
