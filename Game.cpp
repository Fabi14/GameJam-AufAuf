#include "Game.h"
#include "olcPGEX_Gamepad/olcPGEX_Gamepad.h"

namespace{
	olc::vd2d calcCenter(const olc::Renderable& renderable)
	{
		if (renderable.Sprite())
		{
			return { renderable.Sprite()->width / 2., renderable.Sprite()->height / 2. };
		}
		return {};
	}
}

bool Game::OnUserCreate()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	m_imageRoom.Load("assets\\Bedroom1.png");
	m_imageSheep.Load("assets\\Sheep.png");
	m_imageWecker.Load("assets\\Wecker.png");

	m_vecPlayer.push_back(Player{ Input{KeyBinding_WASD,this}, olc::RED });
	m_vecPlayer.push_back(Player{ Input{KeyBinding_Arrows,this}, olc::BLUE });

	olc::GamePad::init();

	return true;
}

bool Game::OnUserUpdate(float fElapsedTime) 
{
	if (GetKey(olc::ESCAPE).bPressed)
	{
		return false;
	}

	//if (gamepad == nullptr || !gamepad->stillConnected) {
	//	DrawString(10, 10, "Press the select button on a gamepad!");
	//	gamepad = olc::GamePad::selectWithButton(olc::GPButtons::FACE_R);
	//	return true;
	//}

	//if (!gamepad->getButton(olc::GPButtons::FACE_D).bHeld) {
	//	FillRect(10, 10, 30, 10, olc::WHITE * gamepad->getAxis(olc::GPAxes::TL));
	//	DrawRect(10, 10, 30, 10, olc::RED);
	//	return true;
	//}
	//else {
	//	FillRect(10, 10, 30, 10, olc::WHITE * gamepad->getAxis(olc::GPAxes::TL));
	//	DrawRect(10, 10, 30, 10, olc::BLUE);
	//	return true;
	//}

	onDraw();
	if (m_win) 
	{
		return true;
	}

	for (auto& sheepPos : m_vecSheepPos)
	{
		sheepPos.onUpdate(fElapsedTime);
	}
	m_weckerPos.onUpdate(fElapsedTime);

	for (int i = 0; i < m_vecPlayer.size(); ++i)
	{
		auto pos = m_vecPlayer[i].handleInput(this, fElapsedTime);
		if (pos)
		{
			auto min = m_weckerPos.getPos();
			auto max = m_weckerPos.getPos() + olc::vd2d{ static_cast<double>(m_imageWecker.Sprite()->width),static_cast<double>( m_imageWecker.Sprite()->height) };
			if (pos->x > min.x && pos->x < max.x && pos->y > min.y && pos->y < max.y)
			{
				m_win = i;
			}
		}
	}

	return true;
}

void Game::onDraw()
{
	Clear(olc::BLACK);
	DrawDecal(olc::vd2d{ 0.,0. }, m_imageRoom.Decal());

	DrawDecal(m_weckerPos.getPos(), m_imageWecker.Decal());

	if (!m_win)
	{
		auto offset = calcCenter(m_imageSheep);
		for (const auto& sheepPos : m_vecSheepPos)
		{
			DrawDecal(sheepPos.getPos() - offset, m_imageSheep.Decal());
		}
	}
	for (const auto& player : m_vecPlayer)
	{
		player.onDraw(this);
	}

	if (m_win)
	{
		DrawStringDecal({ 300.,300. }, "WIN", m_vecPlayer[*m_win].getColor(), {20.,20.});
	}
}