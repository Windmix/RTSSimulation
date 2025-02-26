#pragma once
#include "State.h"
#include "Scout.h"
class ScoutingState : public State<Scout>
{

public:
	static std::shared_ptr<ScoutingState> instance();
	void handle(std::shared_ptr<Scout> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void enterState(std::shared_ptr<Scout> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void exitState(std::shared_ptr<Scout> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;

	bool onMessage(std::shared_ptr<Scout> SPScout, Telegram& telegram) override;
};