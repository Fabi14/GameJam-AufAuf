#include "LevelFindWecker.h"
#include "Helper.h"
#include "Game.h"
#include <ranges>

bool LevelFindWecker::OnUserCreate()
{

	m_imageSheep.Load("assets\\Sheep1.png");
	m_imageWecker.Load("assets\\Wecker1.png");

	std::generate_n(std::back_inserter(m_vecSheepPos), 100, [&]() {return RandomMovePos{ m_imageSheep.Sprite()->Size() }; });
	m_weckerPos = RandomMovePos{ m_imageWecker.Sprite()->Size() };

    return true;
}

std::unique_ptr<Level> LevelFindWecker::OnUserUpdate(float fElapsedTime)
{
	onDraw();
	if (m_win)
	{
		return nullptr;
	}
	timer -= fElapsedTime;
	if (timer < 0.)
	{
		auto nextLevel = std::make_unique<Menu>(m_pge);
		nextLevel->OnUserCreate();
		return nextLevel;
	}


	for (auto& sheepPos : m_vecSheepPos)
	{
		sheepPos.onUpdate(fElapsedTime);
	}
	m_weckerPos->onUpdate(fElapsedTime);

	for (int i = 0; i < m_pge->m_vecPlayer.size(); ++i)
	{
		auto pos = m_pge->m_vecPlayer[i]->handleInput(m_pge, fElapsedTime);
		if (pos)
		{
			auto min = m_weckerPos->getPos() - 0.5 * olc::vd2d{ static_cast<double>(m_imageWecker.Sprite()->width),static_cast<double>(m_imageWecker.Sprite()->height) };
			auto max = m_weckerPos->getPos() + 0.5 * olc::vd2d{ static_cast<double>(m_imageWecker.Sprite()->width),static_cast<double>(m_imageWecker.Sprite()->height) };
			if (pos->x > min.x && pos->x < max.x && pos->y > min.y && pos->y < max.y)
			{
				m_win = i;
				m_pge->m_vecPlayer[i]->addPoint();
			}
			else
			{
				m_pge->m_vecPlayer[i]->block();
			}
		}
	}

    return nullptr;
}

void LevelFindWecker::onDraw()
{
	m_pge->Clear(olc::BLACK);
	m_pge->DrawDecal(olc::vd2d{ 0.,0. }, m_pge->m_imageRoom.Decal());

	auto offset = calcCenter(m_imageWecker);
	m_pge->DrawDecal(m_weckerPos->getPos() - offset, m_imageWecker.Decal());

	if (!m_win)
	{
		auto offset = calcCenter(m_imageSheep);
		for (const auto& sheepPos : m_vecSheepPos)
		{
			olc::vf2d scale = sheepPos.getDir().x < 0 ? olc::vf2d{ -1.f,1.f } : olc::vf2d{ 1.f, 1.f };
			m_pge->DrawDecal(sheepPos.getPos() - offset, m_imageSheep.Decal(), scale);
		}
	}
	for (const auto& [i,player] : std::views::enumerate(m_pge->m_vecPlayer))
	{
		player->onDraw(m_pge);
		m_pge->DrawStringDecal({ 100.f+500.f*i,1000.f }, std::to_string(player->getPoints()), player->getColor(), {10.,10.});
	}

	if (m_win)
	{
		if (*m_win == 0)
		{
			m_pge->DrawStringDecal({ 800.,300. }, "WIN", olc::RED, { 20.,20. });
		}
		else
		{
			m_pge->DrawStringDecal({ 300.,300. }, "WIN", olc::BLUE, { 20.,20. });
		}
		
		m_pge->DrawStringDecal(olc::vd2d{ 900.,1000. }, "SPACE", olc::DARK_GREY, { 5.f,5.f });

		if (m_pge->GetKey(olc::SPACE).bPressed)
		{
			m_win = std::nullopt;
			m_weckerPos = RandomMovePos{ m_imageWecker.Sprite()->Size() };
			std::generate_n(std::back_inserter(m_vecSheepPos), 20, [&]() {return RandomMovePos{ m_imageSheep.Sprite()->Size() }; });
		}
	}
	m_pge->DrawStringDecal(olc::vd2d{ 900.,50. }, std::to_string(timer), olc::DARK_GREY, {5.f,5.f});
}