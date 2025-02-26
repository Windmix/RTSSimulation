#pragma once
#include "State.h"
#include "CoalMiner.h"
class MakingCoalState : public State<CoalMiner>
{
public:
	static std::shared_ptr<MakingCoalState> instance();
	void handle(std::shared_ptr<CoalMiner> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void enterState(std::shared_ptr<CoalMiner> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void exitState(std::shared_ptr<CoalMiner> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;

	bool onMessage(std::shared_ptr<CoalMiner> SPCoalMiner, Telegram& telegram) override;
};