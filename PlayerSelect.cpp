#include "PlayerSelect.h"
#include "Game.h"
#include <ranges>
#include <memory>
#include "Player.h"

bool PlayerSelect::OnUserCreate()
{
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(Input{KeyBinding_WASD, m_pge}, olc::RED, "assets\\HandLeft.png" , olc::vd2d{500.,500.}));
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(Input{KeyBinding_Arrows, m_pge},olc::BLUE, "assets\\HandRight.png", olc::vd2d{700.,500.} ));
    return true;
}

std::unique_ptr<Level> PlayerSelect::OnUserUpdate(float fElapsedTime)
{
    m_pge->Clear(olc::BLACK);
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());

    for (const auto& player : m_pge->m_vecPlayer)
    {
        player->onDraw(m_pge);
    }

    m_pge->DrawStringDecal({ 550.,400. }, "E", olc::GREY, {5.f,5.f});
    m_pge->DrawStringDecal({ 750.,400. }, "NP0", olc::GREY, { 5.f,5.f });


    for (const auto& player : m_pge->m_vecPlayer)
    {
        player->onDraw(m_pge);
    }
    for (auto& player : m_pge->m_vecPlayer)
    {
        if (player->handleInput(m_pge, fElapsedTime))
        {
            player->setActive();
            m_canStart = true;
        }
    }

    if (m_canStart)
    {
        m_pge->DrawStringDecal(olc::vd2d{ 900.,1000. }, "SPACE", olc::DARK_GREY, { 5.f,5.f });
    }
    
    if (m_pge->GetKey(olc::SPACE).bPressed)
    {
        auto nextLevel = std::make_unique<LevelFindWecker>(m_pge);
        nextLevel->OnUserCreate();
        std::erase_if(m_pge->m_vecPlayer, [](const auto& player) { return player && !player->isActive(); });
        return nextLevel;
    }

    return nullptr;
}
