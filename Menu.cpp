#include "Menu.h"
#include "Game.h"

bool Menu::OnUserCreate()
{
    return false;
}

void Menu::onLoad()
{
}

std::unique_ptr<Level> Menu::OnUserUpdate(float fElapsedTime)
{
    m_pge->Clear(olc::BLACK);
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());

    if (m_pge->GetKey(olc::SPACE).bPressed)
    {
        auto nextLevel = std::make_unique<LevelFindWecker>(m_pge);
        nextLevel->OnUserCreate();
        return nextLevel;
    }

    return nullptr;
}
