#include "RandomMovePos.h"
#include "extensions\olcPGEX_SplashScreen.h"
#include "Player.h"
#include "extensions\olcPGEX_Sound.h"
#include "olcPixelGameEngine.h"
#include "olcPGEX_Gamepad/olcPGEX_Gamepad.h"
#include "LevelFindWecker.h"
#include "Menu.h"

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

	olc::Renderable m_imageRoom;
	std::vector<std::unique_ptr<Player>> m_vecPlayer;
private:
	olc::SplashScreen spash;

	olc::GamePad* gamepad = nullptr;

	std::unique_ptr<Level> m_currentLevel{ std::make_unique<Menu>(this) };
};

