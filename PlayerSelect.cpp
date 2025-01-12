#include "PlayerSelect.h"
#include "Game.h"
#include <ranges>
#include <memory>
#include "Player.h"
#include "GameSettings.h"

bool PlayerSelect::OnUserCreate()
{
    m_pge->m_vecPlayer.clear();
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<Input>(KeyBinding_WASD, m_pge), olc::RED, "assets\\HandLeft.png" , olc::vd2d{  GameSettings::gameW / 5. * 2. ,500.}));
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<Input>(KeyBinding_Arrows, m_pge),olc::BLUE, "assets\\HandRight.png", olc::vd2d{ GameSettings::gameW / 5. * 3. ,500.} ));
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<InputGamePad>( m_pge ), olc::YELLOW, "assets\\HandRight.png", olc::vd2d{ GameSettings::gameW / 5. * 1. ,500. }));

    m_imageInputWASD.Load("assets\\wasd.png");
    m_imageInputArrows.Load("assets\\Pfeil.png");

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

    //m_pge->DrawStringDecal({ 550.,400. }, "E", olc::GREY, {5.f,5.f});
    //m_pge->DrawStringDecal({ 750.,400. }, "NP0", olc::GREY, { 5.f,5.f });
    m_pge->DrawDecal(olc::vf2d{ static_cast<float>(GameSettings::gameW)/5.f * 2.f - static_cast<float>(m_imageInputWASD.Sprite()->Size().x)/2.f, 600.f}, m_imageInputWASD.Decal());
    m_pge->DrawDecal(olc::vf2d{ static_cast<float>(GameSettings::gameW) / 5.f * 3.f - static_cast<float>(m_imageInputWASD.Sprite()->Size().x) / 2.f, 600.f }, m_imageInputArrows.Decal());

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


        if (m_pge->GetKey(olc::SPACE).bPressed)
        {
            auto nextLevel = std::make_unique<LevelFindWecker>(m_pge);
            nextLevel->OnUserCreate();
            std::erase_if(m_pge->m_vecPlayer, [](const auto& player) { return player && !player->isActive(); });
            return nextLevel;
        }
    }

    return nullptr;
}
