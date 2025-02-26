#pragma once
#include "State.h"
#include "Builder.h"
class BuildingState : public State<Builder>
{
public:
	static std::shared_ptr<BuildingState> instance();
	void handle(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void enterState(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void exitState(std::shared_ptr<Builder> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;

	bool onMessage(std::shared_ptr<Builder> SPWBuilder, Telegram& telegram) override;
};