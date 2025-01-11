#include "LevelFindWecker.h"
#include "Helper.h"
#include "Game.h"

bool LevelFindWecker::OnUserCreate()
{

	m_imageSheep.Load("assets\\Sheep.png");
	m_imageWecker.Load("assets\\Wecker.png");

	std::generate_n(std::back_inserter(m_vecSheepPos), 100, [&]() {return RandomMovePos{ m_imageSheep.Sprite()->Size() }; });
	m_weckerPos = RandomMovePos{ m_imageWecker.Sprite()->Size() };

	m_vecPlayer.push_back(Player{ Input{KeyBinding_WASD, m_pge}, olc::RED,"assets\\HandLeft.png" });
	m_vecPlayer.push_back(Player{ Input{KeyBinding_Arrows, m_pge}, olc::BLUE, "assets\\HandRight.png" });
    return true;
}

void LevelFindWecker::onLoad()
{
}

std::unique_ptr<Level> LevelFindWecker::OnUserUpdate(float fElapsedTime)
{
	onDraw();
	if (m_win)
	{
		return nullptr;
	}

	for (auto& sheepPos : m_vecSheepPos)
	{
		sheepPos.onUpdate(fElapsedTime);
	}
	m_weckerPos->onUpdate(fElapsedTime);

	for (int i = 0; i < m_vecPlayer.size(); ++i)
	{
		auto pos = m_vecPlayer[i].handleInput(m_pge, fElapsedTime);
		if (pos)
		{
			auto min = m_weckerPos->getPos();
			auto max = m_weckerPos->getPos() + olc::vd2d{ static_cast<double>(m_imageWecker.Sprite()->width),static_cast<double>(m_imageWecker.Sprite()->height) };
			if (pos->x > min.x && pos->x < max.x && pos->y > min.y && pos->y < max.y)
			{
				m_win = i;
			}
			else
			{
				m_vecPlayer[i].block();
			}
		}
	}

    return nullptr;
}

void LevelFindWecker::onDraw()
{
	m_pge->Clear(olc::BLACK);
	m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());


	m_pge->DrawDecal(m_weckerPos->getPos(), m_imageWecker.Decal());

	if (!m_win)
	{
		auto offset = calcCenter(m_imageSheep);
		for (const auto& sheepPos : m_vecSheepPos)
		{
			m_pge->DrawDecal(sheepPos.getPos() - offset, m_imageSheep.Decal());
		}
	}
	for (const auto& player : m_vecPlayer)
	{
		player.onDraw(m_pge);
	}

	if (m_win)
	{
		m_pge->DrawStringDecal({ 300.,300. }, "WIN", m_vecPlayer[*m_win].getColor(), { 20.,20. });
	}
}