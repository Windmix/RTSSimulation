#include "Clock.h"

Clock::Clock()
{
    this->time = 0;
}
std::shared_ptr<Clock> Clock::instance()
{
    static std::shared_ptr<Clock> clock = std::make_shared<Clock>();
    return clock;
}
