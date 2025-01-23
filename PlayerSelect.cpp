#include "PlayerSelect.h"
#include "Game.h"
#include <ranges>
#include <memory>
#include "Player.h"
#include "GameSettings.h"

bool PlayerSelect::OnUserCreate()
{
    m_pge->m_vecPlayer.clear();
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<Input>(KeyBinding_WASD, m_pge),   olc::Pixel(161,82,82), "assets\\HandLeft.png", olc::vd2d{GameSettings::gameW / 5. * 2. ,500.}, "assets\\ScoreboxRed.png"));
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<Input>(KeyBinding_Arrows, m_pge), olc::Pixel(82,106,161), "assets\\HandRight.png", olc::vd2d{ GameSettings::gameW / 5. * 3. ,500.}, "assets\\ScoreboxBlue.png"));
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<InputGamePad>( m_pge ),           olc::Pixel(201,190,73), "assets\\ControllerHandLeft.png", olc::vd2d{ GameSettings::gameW / 5. * 1. ,500. }, "assets\\ScoreboxYellow.png"));
    m_pge->m_vecPlayer.emplace_back(std::make_unique<Player>(std::make_unique<InputGamePad>( m_pge ),           olc::Pixel(82,161,91), "assets\\ControllerHandRight.png", olc::vd2d{ GameSettings::gameW / 5. * 4. ,500. }, "assets\\ScoreboxGreen.png"));


    m_imageInputWASD.Load("assets\\wasd.png");
    m_imageInputArrows.Load("assets\\Pfeil.png");
    m_imageInputController.Load("assets\\Controller.png");

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
    m_pge->DrawDecal(olc::vf2d{ static_cast<float>(GameSettings::gameW) / 5.f * 3.f - static_cast<float>(m_imageInputArrows.Sprite()->Size().x) / 2.f, 600.f }, m_imageInputArrows.Decal());
    m_pge->DrawDecal(olc::vf2d{ static_cast<float>(GameSettings::gameW) / 5.f * 1.f - static_cast<float>(m_imageInputController.Sprite()->Size().x) / 2.f, 600.f }, m_imageInputController.Decal());
    m_pge->DrawDecal(olc::vf2d{ static_cast<float>(GameSettings::gameW) / 5.f * 4.f - static_cast<float>(m_imageInputController.Sprite()->Size().x) / 2.f, 600.f }, m_imageInputController.Decal());


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
