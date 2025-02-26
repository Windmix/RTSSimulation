#pragma once
#include <string>
#include <memory>
#include "BaseGameEntity.h"
#include "State.h"
#include "AstarAlgorithm.h"



// Forward declare State
template<class entityType>
class State;



class Builder : public BaseGameEntity, public std::enable_shared_from_this<Builder>
{
public:

	std::string name;
	float frameCounter;
	float speed;
	float buildingTimer;
	std::vector<std::shared_ptr<GameObjectX>> path;

	std::shared_ptr<GameObjectX> currentStandingGameObject;

	std::shared_ptr<State<Builder>> currentState;

	Builder(std::string name);

	void handleMessage(Telegram& msg) override;
	void drawPath() override;
	void update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;




};