#include "Scoreboard.h"
#include "Menu.h"
#include "Game.h"
#include <ranges>


namespace
{
    std::vector<Score> scores;
}

void Scoreboard::addPoints(const std::vector<Score>& points)
{
    scores.insert_range(scores.end(), points);
    std::ranges::sort(scores, std::greater{}, &Score::points);
}

bool Scoreboard::OnUserCreate()
{
    return false;
}

std::unique_ptr<Level> Scoreboard::OnUserUpdate(float fElapsedTime)
{
    if (m_pge->GetKey(olc::SPACE).bPressed)
    {
        auto nextLevel = std::make_unique<Menu>(m_pge);
        nextLevel->OnUserCreate();
        return nextLevel;
    }

    m_pge->Clear(olc::BLACK);
    m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());

    for (const auto& [i, score] : std::views::enumerate(scores))
    {
        m_pge->DrawStringDecal({ 800.f,500.f + 100.f * i }, std::to_string(score.points), score.color, {10.f,10.f});
    }

    return nullptr;
}
