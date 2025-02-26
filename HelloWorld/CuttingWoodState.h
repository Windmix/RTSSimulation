#pragma once
#include "State.h"
#include "Worker.h"
class CuttingWoodState : public State<Worker>
{

public:
	static std::shared_ptr<CuttingWoodState> instance();
	void handle(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void enterState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;
	void exitState(std::shared_ptr<Worker> owner, std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;

	bool onMessage(std::shared_ptr<Worker> SPWorker, Telegram& telegram) override;
};