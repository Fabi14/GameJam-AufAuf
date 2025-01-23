#include "Menu.h"
#include "Game.h"
#include "PlayerSelect.h"

bool Menu::OnUserCreate()
{
    m_imageTitle.Load("assets\\Title.png");
    m_imageCredits.Load("assets\\Credits.png");
    return false;
}

std::unique_ptr<Level> Menu::OnUserUpdate(float fElapsedTime)
{
    m_pge->Clear(olc::BLACK);
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_imageTitle.Decal());
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_imageCredits.Decal());

    m_pge->DrawStringDecal(olc::vd2d{ 900.,1000. }, "SPACE", olc::DARK_GREY, {5.f,5.f});

    if (m_pge->GetKey(olc::SPACE).bPressed)
    {
        auto nextLevel = std::make_unique<PlayerSelect>(m_pge);
        nextLevel->OnUserCreate();
        return nextLevel;
    }

    return nullptr;
}
