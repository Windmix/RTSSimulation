#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "PlayerMap.h"
#include "AstarAlgorithm.h"
#include "MessageDispatcher.h"
#include "EntityManager.h"
#include "DataControllerEntities.h"
#include "DataControllerTrees.h"
#include "Builder.h"
#include "CoalMiner.h"
#include "Clock.h"

#include <iomanip>
#include <string>




int DISPLAY_WIDTH = 1920;
int DISPLAY_HEIGHT = 1000;
int DISPLAY_SCALE = 1;

//singletons
std::shared_ptr<PlayerMap> pMap = PlayerMap::Instance();
std::shared_ptr<AstartAlgorithm> AstAlgorithm = AstartAlgorithm::Instance(); // singleton
std::shared_ptr<MessageDispatcher> messageDispatcher = MessageDispatcher::instance();
std::shared_ptr<DataControllerEntities> dataControllerEntities = DataControllerEntities::instance();
std::shared_ptr<DataControllerTrees> dataControllerTrees = DataControllerTrees::instance();
std::shared_ptr<Clock> theClock = Clock::instance();
std::shared_ptr<Constants> constants = Constants::instance();


//random
float fps = 0.0f;
float fpsTimer = 0.0f;
bool pause = false;
float timer = 0.0f;

//entities
std::shared_ptr<Scout> scout;
std::shared_ptr<Worker> worker;
std::shared_ptr<Builder> builder;



// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{

	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );

	pMap->readMapFromFile("../maps/MapSimulation.txt");
	constants->readFromFile("../maps/Constants.txt");
	//pMap->randomizeMap();
	pMap->SettingUpMap(DISPLAY_WIDTH / 5, -20, 10);

	for (int i = 0; i < constants->totalWorkers; i++)
	{

		worker = std::make_shared<Worker>("Agent_" + to_string(worker->getNextValidID()),constants->speed * constants->simulationSpeed);
		worker->setEntityID(worker->getNextValidID());
		worker->currentStandingGameObject = pMap->getStartObject();
		Entity_Manager->registerEntity(worker);
		dataControllerEntities->TotalWorkers.push_back(worker);
	}
	


	
	

}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	constants->readFromFile("../maps/Constants.txt");
	// FPS Calculation
	frameCount++;
	fpsTimer += elapsedTime;
	if (fpsTimer >= 1.0f)
	{
		fps = frameCount / fpsTimer;
		frameCount = 0;
		fpsTimer = 0.0f;
	}

	Play::ClearDrawingBuffer(Play::cBlack); // clear display using color provided

	theClock->time += elapsedTime * constants->simulationSpeed;
	pMap->drawMap();
	pMap->DrawTrees();


	for (auto& entity : Entity_Manager->getAllEntities())
	{
		entity.second->update(pMap, AstAlgorithm, elapsedTime);

		
	}
	/*for (auto& scout : dataControllerEntities->totalScouts)
	{
		DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 160), ("Scout_Tile_ID " + std::to_string(scout->currentStandingGameObject->ID)).c_str(), Play::cGreen, true);
	}*/

	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4), ("TotaL_Workers: " + std::to_string(dataControllerEntities->TotalWorkers.size())).c_str(), Play::cYellow, true);
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 20), ("Total_Scouts: " + std::to_string(dataControllerEntities->totalScouts.size())).c_str(), Play::cYellow, true);
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 40), ("Total_builders " + std::to_string(dataControllerEntities->TotalBuilders.size())).c_str(), Play::cYellow, true);
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 60), ("Total_Wood_Count: " + std::to_string(dataControllerEntities->getInventoryWoodforAllWorkers())).c_str(), Play::cYellow, true);
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 80), ("Total_Found_Trees: " + std::to_string(dataControllerTrees->foundTrees.size())).c_str(), Play::cYellow, true);
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 100),("current_Time: " + []()
		{
			std::ostringstream ss;
			ss << std::fixed << std::setprecision(2) << theClock->time;  // Round to 2 decimal places
			return ss.str();
			}()).c_str(),
				Play::cYellow, true);
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 120), ("Priority_Queue size: " + std::to_string(messageDispatcher->getPriorityQ().size())).c_str(), Play::cYellow, true);

	if ((pMap->getCoalMilObject()!= nullptr))
	{
		DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 140), ("wood_total_coal_mil: " + std::to_string(pMap->getCoalMilObject()->totalWood)).c_str(), Play::cCyan, true);
		DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 180), ("Coal_total_coal_mil: " + std::to_string(pMap->getCoalMilObject()->TotalCoal)).c_str(), Play::cOrange, true);
		if (pMap->getCoalMilObject()->TotalCoal >= 200 && !pause)
		{
			timer = theClock->time;
			pause = true;
		}
		DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 280, DISPLAY_HEIGHT / 4 - 200), ("200_coal_Timer_finish: " + std::to_string(timer) + " in_hours: " + std::to_string(timer/3600)).c_str(), Play::cWhite, true);
	}
	else
	{

	}
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT / 4 - 160), ("Total_Coal_Miners: " + std::to_string(dataControllerEntities->TotalCoalMiners.size())).c_str(), Play::cGreen, true);
	
	
	DrawDebugText(Point2D(DISPLAY_WIDTH / 4 - 300, DISPLAY_HEIGHT - 100),("FPS: " + std::to_string(static_cast<int>(fps))).c_str(),Play::cGreen, true);



	messageDispatcher->dispatchDelayedMessages();

	Play::PresentDrawingBuffer();
	return Play::KeyDown( KEY_ESCAPE );
}
// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

