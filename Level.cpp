#include "Level.h"

bool Level::OnUserCreate()
{
    return false;
}


std::unique_ptr<Level> Level::OnUserUpdate(float fElapsedTime)
{
    return nullptr;
}
