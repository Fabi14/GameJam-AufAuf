#include "Scoreboard.h"
#include "Menu.h"
#include "Game.h"
#include <ranges>
#include "GameSettings.h"


namespace
{
    //std::vector<Score> scores;
}

void Scoreboard::addPoints(const std::vector<Score>& points)
{
    scores.insert_range(scores.end(), points);
    std::ranges::sort(scores, std::greater{}, &Score::points);
}

bool Scoreboard::OnUserCreate()
{
    m_win.Load("assets\\Winbox.png");


    auto getImage = [](auto path)
        {
            olc::Renderable image;
            image.Load(path);
            return image;
        };
    
    m_mapWinner.push_back(std::make_pair(olc::Pixel(161,82,82),  getImage("assets\\WinRed.png")));
    m_mapWinner.push_back(std::make_pair(olc::Pixel(82,106,161), getImage("assets\\WinBlue.png")));
    m_mapWinner.push_back(std::make_pair(olc::Pixel(201,190,73), getImage("assets\\WinYellow.png")));
    m_mapWinner.push_back(std::make_pair(olc::Pixel(82,161,91),  getImage("assets\\WinGreen.png")));
    return false;
}

std::unique_ptr<Level> Scoreboard::OnUserUpdate(float /*fElapsedTime*/)
{
    if (m_pge->GetKey(olc::SPACE).bPressed)
    {
        auto nextLevel = std::make_unique<Menu>(m_pge);
        nextLevel->OnUserCreate();
        return nextLevel;
    }

    m_pge->Clear(olc::BLACK);
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());

    m_pge->DrawDecal({ static_cast<float>(GameSettings::gameW) / 2.f - static_cast<float>(m_win.Sprite()->Size().x) / 2.f , 200}, m_win.Decal());

    auto it = std::ranges::find_if(m_mapWinner, [&](const auto& p) {return p.first == scores.front().color; });
    if (it != m_mapWinner.end())
    {
        m_pge->DrawDecal({ static_cast<float>(GameSettings::gameW) / 2.f - static_cast<float>(m_win.Sprite()->Size().x) / 2.f , 200 }, it->second.Decal());
    }
    m_pge->DrawStringDecal(olc::vd2d{ 900.,1000. }, "SPACE", olc::DARK_GREY, { 5.f,5.f });

    for (const auto& [i, score] : std::views::enumerate(scores))
    {
        m_pge->DrawStringDecal({ 800.f,500.f + 100.f * i }, std::to_string(score.points), score.color, {10.f,10.f});
    }

    return nullptr;
}
