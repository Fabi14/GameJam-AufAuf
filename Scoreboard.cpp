#include "Scoreboard.h"
namespace
{
    std::vector<int> scores;
}

void Scoreboard::addPoints(const std::vector<int>& points)
{
    scores.insert_range(scores.end(), points);
}

bool Scoreboard::OnUserCreate()
{
    return false;
}

std::unique_ptr<Level> Scoreboard::OnUserUpdate(float fElapsedTime)
{
    return nullptr;
}
