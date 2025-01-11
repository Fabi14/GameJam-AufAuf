#include "RandomMovePos.h"
#include "extensions\olcPGEX_SplashScreen.h"
#include "Player.h"
#include "extensions\olcPGEX_Sound.h"
#include "olcPixelGameEngine.h"
#include "olcPGEX_Gamepad/olcPGEX_Gamepad.h"

#pragma once
class Game : public olc::PixelGameEngine
{
public:
	Game()
	{
		// Name your application
		sAppName = "Example";
	}

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;

private:
	void onDraw();

	olc::Renderable m_imageRoom;
	olc::Renderable m_imageSheep;
	olc::Renderable m_imageWecker;

	std::vector<RandomMovePos> m_vecSheepPos{200};
	RandomMovePos m_weckerPos;

	std::vector<Player> m_vecPlayer;
	std::optional<int> m_win{ std::nullopt };

	olc::SplashScreen spash;

	olc::GamePad* gamepad = nullptr;
};

