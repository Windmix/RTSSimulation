#pragma once
#include <string>
#include <memory>
#include "BaseGameEntity.h"
#include "Telegram.h"
#include "State.h"
#include "Scout.h"

// Forward declare State
template<class entityType>
class State;

class Worker : public BaseGameEntity, public std::enable_shared_from_this<Worker>
{
public:
    std::string name;
    std::vector<std::shared_ptr<GameObjectX>> path;
    std::shared_ptr<GameObjectX> currentStandingGameObject;
    std::shared_ptr<State<Worker>> currentState;

    Telegram holdingMessage;
    float speed;

    int wood;
    int coal;
    int iron;

    float upgradeCompleteTime;
    float cuttingCompleteTime;

    bool isUpgradingBuilder;
    bool isUpgradingScout;
    bool isUpgradingCoalMiner;

    int ammoutIsConverting;
    bool isBusy;

    Worker(std::string name, float speed);

    void handleMessage(Telegram& msg) override;
    bool isWoodFull();
    bool hasUpgradedScout();
  
    void drawPath() override;
    void update(std::shared_ptr<PlayerMap>& pMap, std::shared_ptr<AstartAlgorithm>& astarAlgo, float deltaTime) override;

    float frameCounter;
};