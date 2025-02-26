#pragma once
#include <string>
#include <memory>
#include "BaseGameEntity.h"
#include "State.h"
#include "AstarAlgorithm.h"



// Forward declare State
template<class entityType>
class State;



class CoalMiner : public BaseGameEntity, public std::enable_shared_from_this<CoalMiner>
{
public:

	std::string name;
	float frameCounter;
	float speed;
	std::vector<std::shared_ptr<GameObjectX>> path;
	float innerTimer;
	std::shared_ptr<GameObjectX> currentStandingGameObject;

	std::shared_ptr<State<CoalMiner>> currentState;

	CoalMiner(std::string name);

	void handleMessage(Telegram& msg) override;
	void drawPath() override;
	void update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;




};