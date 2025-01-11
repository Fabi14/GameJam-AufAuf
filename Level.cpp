#include "Level.h"

bool Level::OnUserCreate()
{
    return false;
}

void Level::onLoad()
{

}

std::unique_ptr<Level> Level::OnUserUpdate(float fElapsedTime)
{
    return nullptr;
}
