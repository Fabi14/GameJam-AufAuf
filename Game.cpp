#include "Game.h"

namespace{
	olc::vd2d calcCenter(const olc::Renderable& renderable)
	{
		if (renderable.Sprite())
		{
			return { renderable.Sprite()->width / 2., renderable.Sprite()->height / 2. };
		}
	}
}

bool Game::OnUserCreate()
{
	std::srand(std::time(nullptr));

	m_imageRoom.Load("assets\\Bedroom1.png");
	m_imageSheep.Load("assets\\Sheep.png");
	m_imageWecker.Load("assets\\Wecker.png");

	m_vecPlayer.push_back(Player{ KeyBinding_WASD, olc::RED});
	m_vecPlayer.push_back(Player{ KeyBinding_Arrows, olc::BLUE });

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime) 
{
	onDraw();
	for (auto& sheepPos : m_vecSheepPos)
	{
		sheepPos.onUpdate(fElapsedTime);
	}
	m_weckerPos.onUpdate(fElapsedTime);

	for (auto& player : m_vecPlayer)
	{
		player.handleInput(this,fElapsedTime);
	}

	if (GetKey(olc::ESCAPE).bPressed)
	{
		return false;
	}
	return true;
}

void Game::onDraw()
{
	Clear(olc::BLACK);
	DrawDecal(olc::vd2d{ 0.,0. }, m_imageRoom.Decal());

	DrawDecal(m_weckerPos.pos, m_imageWecker.Decal());

	auto offset = calcCenter(m_imageSheep);
	for (const auto& sheepPos : m_vecSheepPos)
	{
		DrawDecal(sheepPos.pos- offset, m_imageSheep.Decal());
	}
	for (const auto& player : m_vecPlayer)
	{
		player.onDraw(this);
	}
}