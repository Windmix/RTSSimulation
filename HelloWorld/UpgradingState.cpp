#include "UpgradingState.h"
#include "Scout.h"
#include "EntityManager.h"
#include "DataControllerEntities.h"
#include "Clock.h"
#include "ScoutingState.h"
#include "BuildingState.h"
#include "MakingCoalState.h"
std::shared_ptr<UpgradingState> UpgradingState::instance()
{
    static std::shared_ptr<UpgradingState> instance = std::make_shared<UpgradingState>();
    return instance;
}

void UpgradingState::handle(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
   
    std::shared_ptr<Clock> theClock = Clock::instance();

    // If the upgrade time has passed, convert to a Scout
   
    if (theClock->time >= owner->upgradeCompleteTime && owner->isUpgradingScout)
    {
        // Create the new Scout entity based on the current worker (owner)
        std::shared_ptr<Scout> scout = std::make_shared<Scout>(owner->name);
        scout->currentStandingGameObject = owner->currentStandingGameObject;
        scout->speed = owner->speed;
        scout->currentState = ScoutingState::instance();

        std::shared_ptr<DataControllerEntities> dataControllerEntities = DataControllerEntities::instance();

        // Save the entity ID before removing the old entity from the map
        int entityIDTemp = owner->getEntityID();

        // Set the entity ID for the new Scout
        scout->setEntityID(entityIDTemp);

        // Register the new entity (Scout) in the entity map
        Entity_Manager->registerEntity(scout);

        // Add the new Scout to the list of total scouts
        dataControllerEntities->totalScouts.push_back(scout);

        // Remove the old Worker from the worker list
        auto& workers = dataControllerEntities->TotalWorkers;
        workers.erase(std::remove_if(workers.begin(), workers.end(),
            [&](std::shared_ptr<Worker> w) { return w->getEntityID() == scout->getEntityID(); }),
            workers.end());

       
    }
    //upgrading builder
    if (theClock->time >= owner->upgradeCompleteTime && owner->isUpgradingBuilder)
    {
        std::shared_ptr<Builder> builder = std::make_shared<Builder>(owner->name);
        builder->currentStandingGameObject = owner->currentStandingGameObject;
        builder->speed = owner->speed;
        builder->currentState = BuildingState::instance();

        std::shared_ptr<DataControllerEntities> dataControllerEntities = DataControllerEntities::instance();

        int entityIDTemp = owner->getEntityID();

        // Set the entity ID for the new Builder entity first
        builder->setEntityID(entityIDTemp);

        // Register the new Builder entity in the entity map
        Entity_Manager->registerEntity(builder);

        // Add the new Builder to the list of total builders
        dataControllerEntities->TotalBuilders.push_back(builder);

        // Remove the old Worker from the worker list
        auto& workers = dataControllerEntities->TotalWorkers;
        workers.erase(std::remove_if(workers.begin(), workers.end(),
            [&](std::shared_ptr<Worker> w) { return w->getEntityID() == builder->getEntityID(); }),
            workers.end());

       
    }

    //upgrading CoalMiner
    if (theClock->time >= owner->upgradeCompleteTime && owner->isUpgradingCoalMiner)
    {
        std::shared_ptr<CoalMiner> coalMiner = std::make_shared<CoalMiner>(owner->name);
        coalMiner->currentStandingGameObject = owner->currentStandingGameObject;
        coalMiner->speed = owner->speed;
        coalMiner->currentState = MakingCoalState::instance();

        std::shared_ptr<DataControllerEntities> dataControllerEntities = DataControllerEntities::instance();

        int entityIDTemp = owner->getEntityID();

        // Set the entity ID for the new CoalMiner entity first
        coalMiner->setEntityID(entityIDTemp);

        // Register the new CoalMiner entity in the entity map
        Entity_Manager->registerEntity(coalMiner);

        // Add the new CoalMiner to the list of total coal miners
        dataControllerEntities->TotalCoalMiners.push_back(coalMiner);

        // Remove the old Worker from the worker list
        auto& workers = dataControllerEntities->TotalWorkers;
        workers.erase(std::remove_if(workers.begin(), workers.end(),
            [&](std::shared_ptr<Worker> w) { return w->getEntityID() == coalMiner->getEntityID(); }),
            workers.end());

        
    }
   
    else
    {

    }
 
}

void UpgradingState::enterState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{ 


}

void UpgradingState::exitState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime)
{
}

bool UpgradingState::onMessage(std::shared_ptr<Worker> SPWorker, Telegram& tselegram)
{
    return false;
}
